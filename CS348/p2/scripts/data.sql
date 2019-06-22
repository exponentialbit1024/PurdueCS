--Customer
insert into Customers(CustomerId, FirstName, LastName, City) values (1, 'Cust A', 'Cust Last a', 'Lafayette');
insert into Customers(CustomerId, FirstName, LastName, City) values (2, 'Cust B', 'Cust Last b', 'Lafayette');
insert into Customers(CustomerId, FirstName, LastName, City) values (3, 'Cust C', 'Cust Last c', 'West Lafayette');
insert into Customers(CustomerId, FirstName, LastName, City) values (4, 'Cust D', 'Cust Last d', 'West Lafayette');
insert into Customers(CustomerId, FirstName, LastName, City) values (5, 'Cust E', 'Cust Last e', 'Indianapolis');
insert into Customers(CustomerId, FirstName, LastName, City) values (6, 'Cust F', 'Cust Last f', 'Indianapolis');
insert into Customers(CustomerId, FirstName, LastName, City) values (7, 'Cust G', 'Cust Last g', 'Fort Wayne');
insert into Customers(CustomerId, FirstName, LastName, City) values (8, 'Cust H', 'Cust Last h', 'Fort Wayne');
insert into Customers(CustomerId, FirstName, LastName, City) values (9, 'Cust I', 'Cust Last i', 'Lafayette');
insert into Customers(CustomerId, FirstName, LastName, City) values (10, 'Cust J', 'Cust Last j', 'West Lafayette');

--CarDealers
insert into CarDealers(DealerId, DealerName, City, State) values (1, 'Bob Rohman', 'Lafayette',  'IN');
insert into CarDealers(DealerId, DealerName, City, State) values (2, 'DeFouw', 'Lafayette',  'IN');
insert into CarDealers(DealerId, DealerName, City, State) values (3, 'Tom Wood', 'Indianapolis',  'IN');
insert into CarDealers(DealerId, DealerName, City, State) values (4, 'Kelly', 'Fort Wayne',  'IN');
insert into CarDealers(DealerId, DealerName, City, State) values (5, 'Brown', 'Kokomo',  'MD');
insert into CarDealers(DealerId, DealerName, City, State) values (6, 'North Coast',  'Cleveland', 'OH');


--CarRentalSite
insert into CarRentalSite(CarRentalSiteId, CarRentalSiteName, City) values (1, 'Hertz', 'Lafayette');
insert into CarRentalSite(CarRentalSiteId, CarRentalSiteName, City) values (2, 'Enterprise', 'Indianapolis');
insert into CarRentalSite(CarRentalSiteId, CarRentalSiteName, City) values (3, 'Alamo', 'Fort Wayne');
insert into CarRentalSite(CarRentalSiteId, CarRentalSiteName, City) values (4, 'Avis', 'Lafayette');
insert into CarRentalSite(CarRentalSiteId, CarRentalSiteName, City) values (5, 'Budget', 'West Lafayette');


--Car
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (1, 'Chevy Spark', 'compact', 1, 20.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (2, 'Nissan Versa', 'compact', 2, 25.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (3, 'Audi', 'luxury', 3, 200);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (4, 'Porsche', 'luxury', 4, 350);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (5, 'Chrysler', 'van', 2, 47);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (6, 'Jeep', 'SUV', 5, 53);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (7, 'Ford Focus', 'compact', 6, 23.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (8, 'Honda CRV', 'SUV', 5, 30.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (9, 'Toyota Echo', 'compact', 6, 27.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (10, 'Chevy', 'Truck', 5, 45);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (11, 'Toyota Yaris', 'compact', 4, 29.0);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (12, 'Ford', 'Truck', 6, 55);
insert into Car(CarId, CarName, Category, DealerId, SuggestedDealerRentalPrice) values (13, 'Honda Odyssey', 'van', 4, 57);


--RentalInventories
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (1,1,10);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (10,1,20);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (5,1,10);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (8,1,3);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (11,2,8);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (9,2,5);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (2,2,4);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (4,2,3);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (13,2,2);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (9,3,5);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (11,3,3);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (6,3,1);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (9,4,2);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (12,4,3);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (6,4,2);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (4,4,1);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (7,5,5);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (3,5,1);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (4,5,1);
insert into RentalInventories(CarId, CarRentalSiteId, TotalCars) values (6,5,3);



--Rentals
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (1,1,1,1,15,25, to_date('20180101','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (2,2,1,10,12,50, to_date('20180102','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (3,2,1,5,21,60, to_date('20180103','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (4,3,5,7,1,27, to_date('20180104','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (5,4,5,3,3,245, to_date('20180201','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (6,5,2,4,2,400, to_date('20180301','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (7,2,1,5,14,70, to_date('20180202','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (8,6,2,2,2,29, to_date('20180401','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (9,7,3,11,1,33, to_date('20180503','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (10,8,3,11,10,33, to_date('20180601','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (11,9,4,9,2,30, to_date('20180701','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (12,10,1,8,1,42, to_date('20180301','YYYYMMDD'),'BOOKED');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (13,8,3,9,10,30, to_date('20180201','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (14,9,1,5,25,17, to_date('20180501','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (15,5,2,13,6,66, to_date('20180502','YYYYMMDD'),'PERSONAL');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (16,7,4,4,2,370, to_date('20180503','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (17,7,5,6,3,60, to_date('20180503','YYYYMMDD'),'BUSINESS');
insert into Rentals(RentalId, CustomerId, CarRentalSiteId, CarId, numOfDays, RentalRate, RentalDate, Status) values (18,6,2,4,3,400, to_date('20180402','YYYYMMDD'),'PERSONAL');

