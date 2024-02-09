SET SQL_SAFE_UPDATES = 0;
SET GLOBAL FOREIGN_KEY_CHECKS=0;

create database courseproject;
use courseproject;

show tables;

select * from admin;
select * from config;
select * from center;
select * from family;
select * from _group;
select * from migrant;
select * from personal;

delete from admin;
delete from config;
delete from center;
delete from family;
delete from _group;
delete from migrant;
delete from personal;

drop table personal;
drop table migrant;
drop table _group;
drop table family;
drop table center;
drop table config;
drop table admin;

insert into admin (admin_login, admin_password, admin_lastname, admin_firstname, admin_middlename) values ('adminadmin', 'adminadmin', 'Кущевський', 'Андрій', 'Петрович');
insert into config (config_posX, config_posY, config_width, config_length) values ('489', '268', '942', '504');

insert into center(center_id, center_street, center_house, center_general_places, center_available_places) values ('1', 'Робоча', '120', 50, 47);

insert into family(family_id, family_people_amount, family_previous_residence) values('1', '3', 'Маріуполь');

insert into migrant(migrant_center_id, migrant_family_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence)
			 values('1', '1', 'Мартиненко', 'Олег', 'Миколайович', 'Чоловіча', 2022-12-14, 'Маріуполь');
insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values ('789156374', '380676811681', 1991-03-12, 'Немає');

insert into migrant(migrant_center_id, migrant_family_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence)
			 values('1', '1', 'Мартиненко', 'Світлана', 'Володимирівна', 'Жіноча', 2022-12-14, 'Маріуполь');
insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values ('213421342', '380967634781', 1993-03-16, 'Немає');
	
insert into migrant(migrant_center_id, migrant_family_id, migrant_lastname, migrant_firstname, migrant_middlename, migrant_sex, migrant_checkin, migrant_previous_residence)
			 values('1', '1', 'Мартиненко', 'Максим', 'Олегович', 'Чоловіча', 2022-12-14, 'Маріуполь');
insert into personal(personal_passport, personal_telephone, personal_birthday, personal_needs) values ('213421342', '380962154236', 2005-05-03, 'Немає');

#Creating main tables

create table admin
(

	admin_id integer auto_increment primary key not null,
	admin_login varchar(20) not null, 
	admin_password varchar(20) not null, 
    admin_lastname varchar(20) not null,
    admin_firstname varchar(15) not null,
    admin_middlename varchar(20) not null

);
 
create table config
(
	
    config_admin_id integer auto_increment primary key not null,
	config_posX integer not null default '489',
	config_posY integer not null default '268',
	config_width integer not null default '942',
	config_length integer not null default '504',
		
	foreign key(config_admin_id) references admin(admin_id) on delete cascade
    
);

 create table center
 (
 
	center_id integer auto_increment primary key not null,
    center_street varchar(20) not null,
    center_house integer not null,
	center_general_places integer not null default '0',
    center_available_places integer not null default '0'
 
 );
 
 create table family
 (
 
	family_id integer auto_increment primary key not null,
	family_previous_residence varchar(20) not null,
    family_people_amount integer not null
    
 );
 
 create table _group
 (
 
 	group_id integer auto_increment primary key not null,
	group_previous_residence varchar(20) not null,
    group_people_amount integer not null
 
 );
 
 create table migrant
 (
	
    migrant_id integer auto_increment primary key not null, 
    migrant_center_id integer not null,
    migrant_family_id integer null,
    migrant_group_id integer null,
    
    migrant_lastname varchar(20) not null,
    migrant_firstname varchar(15) not null,
    migrant_middlename varchar(20) not null,
    
    migrant_sex enum ('Чоловіча', 'Жіноча') not null,
    migrant_checkin date not null,
    migrant_previous_residence varchar(20) not null,
    
    foreign key(migrant_center_id) references center(center_id),
    foreign key(migrant_family_id) references family(family_id),
    foreign key(migrant_group_id) references _group(group_id)
    
 );
 
 create table personal
 (
	
    personal_migrant_id integer auto_increment primary key not null,
    personal_passport varchar(9) not null,
    personal_telephone varchar(18) null,
    personal_birthday date not null,
    personal_needs tinytext null,
    
    foreign key(personal_migrant_id) references migrant(migrant_id) on delete cascade
    
 );
 
#some other sql scripts

select count(1) from migrant;

delete from migrant where migrant_id = 17;

select * from migrant inner join personal on migrant_id = personal_migrant_id;

update _group set group_people_amount = (group_people_amount - 1) where group_id = 1;

update center set center_available_places = (center_available_places + (select family_people_amount from family where family_id = 1)) where center_id = 1;

select center_street, center_house, count(*) as 'Кол-во людей зарегистрированных на эту дату' from migrant inner join center on migrant_center_id = center_id 
where migrant_checkin >= 2022-11-01 or migrant_checkin <= 2022-11-26 group by center_house group by center_street;

select * from migrant inner join personal on migrant_id = personal_migrant_id where migrant_lastname = :lastname 
or migrant_firstname = :firstname or migrant_middlename = :middlename or migrant_sex = :sex or migrant_checkin = :checkin or migrant_previous_residence = previous_residence;

select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, migrant.migrant_checkin, migrant.migrant_previous_residence 
from migrant inner join personal on migrant_id = personal_migrant_id where migrant_lastname = 'Кущевський';

select migrant.migrant_id, migrant.migrant_center_id, migrant.migrant_family_id, migrant.migrant_group_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex,
                    migrant.migrant_checkin, migrant.migrant_previous_residence from migrant inner join center on migrant_center_id = center_id;

select migrant.migrant_id, migrant.migrant_lastname, migrant.migrant_firstname, migrant.migrant_middlename, migrant.migrant_sex, migrant.migrant_checkin, migrant.migrant_previous_residence 
from migrant inner join personal on migrant_id = personal_migrant_id where migrant_lastname = 'Кущевський' or migrant_firstname = '' or migrant_middlename = '' or migrant_sex = '' or migrant_checkin = 2022-15-11 or migrant_previous_residence = '';
