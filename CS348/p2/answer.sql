set serveroutput on size 32000

-- Question 1: CarRentalSiteDetail detail
create or replace procedure CarRentalSiteDetail (id IN CarRentalSite.CarRentalSiteId%TYPE) as
rentalSiteName varchar(30);
rentalSiteCity varchar(20);
totRentals integer;
mostPopCar varchar(30);
popCarDaysRent integer;
BEGIN
	select CarRentalSiteName, City into rentalSiteName, rentalSiteCity from CarRentalSite where CarRentalSiteId = id;
	dbms_output.put_line(concat('CarRentalSite Name: ', rentalSiteName));
	dbms_output.put_line(concat('CarRentalSite City: ', rentalSiteCity));
	select count(CarRentalSiteId) into totRentals from Rentals where CarRentalSiteId = id;
	dbms_output.put_line(concat('CarRentalSite Total Rentals: ', totRentals));

	select CarName, numOfDays into mostPopCar, popCarDaysRent from (select CarName, max(numOfDays) as numOfDays from (select CarName, CarId, numOfDays, Category from rentals natural join car where category='compact' and carrentalsiteid = id) group by CarName, numOfDays);
	dbms_output.put_line(concat('Most Popular Compact Car: ', mostPopCar));
	dbms_output.put_line(concat('Total Days Rented: ', popCarDaysRent));
END CarRentalSiteDetail;
/

BEGIN
CarRentalSiteDetail(1);
end;
/

-- Question 2:
create or replace procedure MonthlyBusinessRentalsReport as
cursor c is
select count(CarRentalSiteName) as totCount, extract(year from RentalDate) as year, extract(month from RentalDate) as month from Rentals natural join CarRentalSite where status='BUSINESS' group by extract(year from RentalDate), extract(month from RentalDate) order by extract(year from RentalDate), extract(month from RentalDate);
BEGIN
	for n in c loop
		dbms_output.put_line(concat(concat(concat(concat(concat('Total Business Rentals in ', n.year), '-'), n.month), ': '), n.totCount));
		dbms_output.put_line('In Car Rental Sites:');
		for m in (select CarRentalSiteName, sum(numOfDays) as rentDays, extract(year from RentalDate) as year, extract(month from RentalDate) as month from Rentals natural join CarRentalSite where status='BUSINESS' and extract(year from RentalDate)=n.year and extract(month from RentalDate)=n.month group by CarRentalSiteName, extract(year from RentalDate), extract(month from RentalDate) order by CarRentalSiteName) loop
			dbms_output.put_line(concat(concat(concat(concat('- ', m.CarRentalSiteName), ': '), m.rentDays), ' days'));
		end loop;
	end loop;
END MonthlyBusinessRentalsReport;
/
BEGIN
        MonthlyBusinessRentalsReport;
End;
/

-- Question 3:

create or replace procedure MostandLeastProfitCarIndiana as
cursor catcur is
select distinct category from Car;
minAvg integer;
arrCntMin integer := 0;
maxAvg integer;
arrCntMax integer := 0;
type minmaxcar is table of number index by varchar(30);
minc minmaxcar;
maxc minmaxcar;
loopCar varchar(30);
deleteCnt integer;
BEGIN
	for cat in catcur loop
		select min(average) into minAvg from (select CarName, avg(RentalRate - SuggestedDealerRentalPrice) as average from Rentals natural join Car natural join CarDealers where category = cat.category and state='IN' group by CarName);
		for car in (select CarName, avg(RentalRate - SuggestedDealerRentalPrice) from Rentals natural join Car natural join CarDealers where category = cat.category and state='IN' having avg(RentalRate - SuggestedDealerRentalPrice) = minAvg group by CarName) loop
			minc(car.carname) := minAvg;
			arrCntMin := arrCntMin + 1;
		end loop;

		if arrCntMin > 0 then
			arrCntMin := 0;
			dbms_output.put_line(concat('Least Profit in ', cat.category));
			deleteCnt := 0;
			loopCar := minc.first;
			while loopCar is not null loop
				dbms_output.put_line(concat(concat(concat('- ', loopCar), ': '), minc(loopCar)));
				minc.delete(loopCar);
				loopCar := minc.next(loopCar);
			end loop;
		end if;
	end loop;
	
	for cat in catcur loop
		select max(average) into maxAvg from (select CarName, avg(RentalRate - SuggestedDealerRentalPrice) as average from Rentals natural join Car natural join CarDealers where category = cat.category and state='IN' group by CarName);
		for car in (select CarName, avg(RentalRate - SuggestedDealerRentalPrice) from Rentals natural join Car natural join CarDealers where category = cat.category and state='IN' having avg(RentalRate - SuggestedDealerRentalPrice) = maxAvg group by CarName) loop
			maxc(car.carname) := maxAvg;
			arrCntMax := arrCntMax + 1;
		end loop;

		if arrCntMax > 0 then
			arrCntMax := 0;
			dbms_output.put_line(concat('Most Profit in ', cat.category));
			loopCar := maxc.first;
			while loopCar is not null loop
				dbms_output.put_line(concat(concat(concat('- ', loopCar), ': '), maxc(loopCar)));
				maxc.delete(loopCar);
				loopCar := maxc.next(loopCar);
			end loop;
		end if;
	end loop;


END MostandLeastProfitCarIndiana;
/

BEGIN
        MostandLeastProfitCarIndiana;
END;
/

-- Question 4:

create table BusinessRentalCategoryTable(CarRentalSiteId integer, Compact integer, Luxury integer, SUV integer, primary key(CarRentalSiteId));
create or replace procedure BusinessRentalCategory as
compactLength integer;
luxuryLength integer;
suvLength integer;
BEGIN
	for cr in (select carrentalsiteid from CarRentalSite) loop
		BEGIN
		select count(*) as c into compactLength from car c inner join rentals r on c.carid = r.carid where r.status='BUSINESS' and c.category='compact' and r.carrentalsiteid = cr.carrentalsiteid group by r.carrentalsiteid;
		EXCEPTION
			WHEN no_data_found THEN
				compactLength := 0;
		END;
		BEGIN
		select count(*) as c into luxuryLength from car c inner join rentals r on c.carid = r.carid where r.status='BUSINESS' and c.category='luxury' and r.carrentalsiteid = cr.carrentalsiteid group by r.carrentalsiteid;
		EXCEPTION
			WHEN no_data_found THEN
				luxuryLength := 0;
		END;
		BEGIN
		select count(*) as c into suvLength from car c inner join rentals r on c.carid = r.carid where r.status='BUSINESS' and c.category='SUV' and r.carrentalsiteid = cr.carrentalsiteid group by r.carrentalsiteid;
		EXCEPTION
			WHEN no_data_found THEN
				suvLength := 0;
		END;
		insert into BusinessRentalCategoryTable(CarRentalSiteId, Compact, Luxury, SUV) values (cr.carrentalsiteid, compactLength, luxuryLength, suvLength);
	end loop;
END BusinessRentalCategory;
/

BEGIN
BusinessRentalCategory;
END;
/
select * from BusinessRentalCategoryTable;

drop table BusinessRentalCategoryTable;

-- Question 5:

create or replace procedure CarCategoryInventoryInfo(crsid IN CarRentalSite.CarRentalSiteId%TYPE) as
rentalSiteName varchar(30);
BEGIN
	dbms_output.put_line(concat('CarRentalSiteId: ' , crsid));
	select carrentalsitename into rentalSiteName from CarRentalSite where CarRentalSiteId = crsid;
	dbms_output.put_line(concat('CarRentalSiteName: ', rentalSiteName));
	for i in (select cr.carrentalsiteid, cr.carrentalsitename, c.carname, ri.totalcars from ((CarRentalSite cr inner join RentalInventories ri on cr.carrentalsiteid = ri.carrentalsiteid) inner join Car c on c.carid = ri.carid) where cr.carrentalsiteid = crsid order by c.carname asc) loop
		dbms_output.put_line(concat(concat(concat('CarName: ', i.carname), ': '), i.totalcars));
	end loop;
EXCEPTION
	WHEN no_data_found THEN
		dbms_output.put_line('Invalid CarRentalSiteId!');
END CarCategoryInventoryInfo;
/

BEGIN
CarCategoryInventoryInfo(1);
END;
/

BEGIN
CarCategoryInventoryInfo(111);
END;
/
