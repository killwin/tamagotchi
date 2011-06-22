create table tama (
name varchar(50),
state varchar(10),
born bigint,
angry tinyint,
thirst tinyint,
tired tinyint,
mood tinyint,
prety tinyint,
angry_speed tinyint,
thirst_speed tinyint,
id_obj_tama_client integer,
id integer primary key not null auto_increment
)
ENGINE = InnoDB;

create table object (
name varchar(50),
manual varchar(200),
price integer,
id integer primary key not null auto_increment
)
ENGINE = InnoDB;

create table client (
name varchar(50),
passwd varchar(10),
id_obj_tama_client integer, 
id integer primary key not null auto_increment
)
ENGINE = InnoDB;

create table obj_tama_client (
id_client integer,
id_object integer,
id_tama integer,
constraint c_otc foreign key c_otc (id_client) references client(id) on delete set null,
constraint c_obj foreign key c_obj (id_object) references object(id) on delete set null,
constraint c_tam foreign key c_tam (id_tama) references tama(id) on delete set null,
id integer primary key not null auto_increment
)
ENGINE = InnoDB;

