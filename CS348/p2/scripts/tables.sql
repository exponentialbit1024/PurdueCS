create table Customers(CustomerId integer, FirstName varchar(30), LastName varchar(30), City varchar(20), primary key(CustomerId));
create table CarDealers(DealerId integer, DealerName varchar(30), City varchar(20), State varchar(2), primary key(DealerId));
create table CarRentalSite(CarRentalSiteId integer, CarRentalSiteName varchar(30), City varchar(20), primary key(CarRentalSiteId));
create table Car(CarId integer, CarName varchar(30), Category varchar(30), DealerId integer, SuggestedDealerRentalPrice Number(10,4), primary key(CarId));
create table RentalInventories(CarId integer, CarRentalSiteId integer, TotalCars integer);
create table Rentals(RentalId integer, CustomerId integer, CarRentalSiteId integer, CarId integer, numOfDays integer, RentalRate Number(10,4), RentalDate date, Status varchar(15),  primary key(RentalId));
