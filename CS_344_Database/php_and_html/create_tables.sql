DROP TABLE IF EXISTS `sky_faction_category`;
DROP TABLE IF EXISTS `sky_people`;
DROP TABLE IF EXISTS `sky_faction`;
DROP TABLE IF EXISTS `sky_race`;
DROP TABLE IF EXISTS `sky_kingdom`;
DROP TABLE IF EXISTS `sky_weather`; 




CREATE TABLE sky_weather (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	typical_weather VARCHAR(255) NOT NULL,
	PRIMARY KEY (id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO sky_weather(typical_weather) VALUES ('Cold/Wintery');
INSERT INTO sky_weather(typical_weather) VALUES ('Windy/Warm');
INSERT INTO sky_weather(typical_weather) VALUES ('Sunny/Nice');
INSERT INTO sky_weather(typical_weather) VALUES ('Mild');



CREATE TABLE sky_race (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(255) NOT NULL,
	special_ability VARCHAR(255) NOT NULL,
	PRIMARY KEY (id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO sky_race(name, special_ability) VALUES ('Dark Elf', 'Fire Resistant');
INSERT INTO sky_race(name, special_ability) VALUES ('Argonian', 'Breath Under Water');
INSERT INTO sky_race(name, special_ability) VALUES ('Imperial', 'Luck');
INSERT INTO sky_race(name, special_ability) VALUES ('Khajiit', 'Improved Dark Vision');
INSERT INTO sky_race(name, special_ability) VALUES ('Nord', 'Battle Cry');

CREATE TABLE sky_faction (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(255) NOT NULL,
	mission VARCHAR(255) NOT NULL,
	PRIMARY KEY (id)
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO sky_faction(name, mission) VALUES ('Thieves Guild', 'Steal From Everyone / Brotherhood');
INSERT INTO sky_faction(name, mission) VALUES ('Warriors Guild', 'Courageous / Battle Hard');
INSERT INTO sky_faction(name, mission) VALUES ('Mage College', 'Power Through Knowledge');
INSERT INTO sky_faction(name, mission) VALUES ('Nightengale', 'Pursue Stealth');

CREATE TABLE sky_kingdom (
	id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(255) NOT NULL,
	population INT UNSIGNED NOT NULL,
	sky_weatherID INT UNSIGNED,
	PRIMARY KEY (id),
	FOREIGN KEY (sky_weatherID) REFERENCES sky_weather (id) ON DELETE CASCADE ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
INSERT INTO sky_kingdom(name, population, sky_weatherID) VALUES ('Winterhold', '10000', '1');
INSERT INTO sky_kingdom(name, population, sky_weatherID) VALUES ('Solitude', '13000', '2');
INSERT INTO sky_kingdom(name, population, sky_weatherID) VALUES ('Whiterun', '8000', '3');
INSERT INTO sky_kingdom(name, population, sky_weatherID) VALUES ('Riften', '7000', '4');

CREATE TABLE sky_people(
	id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	first_name VARCHAR(255)  NOT NULL,
    last_name VARCHAR(255)  NOT NULL,
    weapon VARCHAR(255)  NOT NULL,
    sky_kingdomID INT UNSIGNED,
    sky_raceID INT UNSIGNED NOT NULL,
	PRIMARY KEY (id),
	INDEX (sky_kingdomID, sky_raceID),
	FOREIGN KEY (sky_kingdomID) REFERENCES sky_kingdom (id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (sky_raceID) REFERENCES sky_race (id) ON DELETE CASCADE ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('Marshal', 'Solidrun', 'Fists', 1, 3);
INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('Jasper', 'Sliger', 'Dagger', 2, 2);
INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('Ulrich', 'StormWind', 'BroadSword', 2, 5);
INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('Valtrew', 'Stricker', 'Sword', 4, 1);
INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ('DragonBorn', 'Highland', 'Staff', 3, 4);



CREATE TABLE sky_faction_category (
	sky_peopleID INT UNSIGNED,
	sky_factionID INT UNSIGNED,
	interesting_note VARCHAR(255),
	PRIMARY KEY (sky_peopleID, sky_factionID),
	INDEX (sky_peopleID, sky_factionID),
	FOREIGN KEY (sky_peopleID) REFERENCES sky_people(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (sky_factionID) REFERENCES sky_faction(id) ON DELETE CASCADE ON UPDATE CASCADE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO sky_faction_category (sky_peopleID, sky_factionID, interesting_note) VALUES (1, 2, 'Fastest Runner');
INSERT INTO sky_faction_category (sky_peopleID, sky_factionID, interesting_note) VALUES (1, 3, 'Smartest');
INSERT INTO sky_faction_category (sky_peopleID, sky_factionID, interesting_note) VALUES (3, 4, 'Great Dancers');
INSERT INTO sky_faction_category (sky_peopleID, sky_factionID, interesting_note) VALUES (2, 1, 'Magic in the sky');
INSERT INTO sky_faction_category (sky_peopleID, sky_factionID, interesting_note) VALUES (3, 2, 'Dragons here');






// Search Queries 

// Query for the race name of the people who are NOT in a user chosen city. 
SELECT skr.name FROM sky_race skr
INNER JOIN sky_people skp ON skp.sky_raceID=skr.id
INNER JOIN sky_kingdom skk ON skk.id = skp.sky_kingdomID
WHERE skk.name <> [kingdom input]
GROUP BY skr.name


// Query for first and last name from sky_people table  of those who are NOT a user chosen race.
SELECT sky_people.first_name, sky_people.last_name FROM sky_people
INNER JOIN sky_race ON sky_race.id=sky_people.sky_raceID 
WHERE sky_race.name <> [race input]
GROUP BY sky_people.first_name 

// Query for the race name of the people who are in a user chosen city. 
SELECT skr.name FROM sky_race skr
INNER JOIN sky_people skp ON skp.sky_raceID=skr.id
INNER JOIN sky_kingdom skk ON skk.id = skp.sky_kingdomID
WHERE skk.name = [kingdom input]
GROUP BY skr.name

// Query for first and last name from sky_people table  of those who are  a user chosen race.
SELECT sky_people.first_name, sky_people.last_name FROM sky_people
INNER JOIN sky_race ON sky_race.id=sky_people.sky_raceID 
WHERE sky_race.name =[race input]
GROUP BY sky_people.first_name 

// Query for the first and last name form sky_people table to see what faction they belong to, ordered by faction.name 
SELECT sky_people.first_name as 'First Name', sky_people.last_name as 'Last Name', sky_faction.name as 'Faction Name'  FROM sky_people
INNER JOIN sky_faction_category sfc ON sfc.sky_peopleID=sky_people.id
INNER JOIN sky_faction on sky_faction.id=sfc.sky_factionID
WHERE sky_people.first_name=[first_name input] AND sky_people.last_name = [last_name input]
ORDER BY sky_faction.name

// Query Kingdom population
SELECT name, population FROM sky_kingdom
WHERE population >= [user input]

// Query a persons weapon of choice
SELECT weapon FROM sky_people
WHERE first_name = [user_input] AND last_name=[user_input] 





// Insert Queries 

// Add a Kingdom
INSERT INTO sky_kingdom(name, population, typical_weather) VALUES ([name input], [population input], [typical_weather input])

// Add a Race
INSERT INTO sky_race(name, special_ability) VALUES ([name input], [special_ability input])

// Add Faction
INSERT INTO sky_faction(name, mission) VALUES ([name input], [mission input])

// Add Faction Category
INSERT INTO sky_faction_category(sky_peopleID, sky_factionID, interesting_note) VALUES ([sky_peopleId input],  [sky_factionID input], [interesting_note input])

// Add a Person
INSERT INTO sky_people(first_name, last_name, weapon, sky_kingdomID, sky_raceID) VALUES ([first_name input], [last_name input], [weapon input], [sky_kingdomId input], [sky_raceId input])


// Updates

// Update Kingdom
UPDATE sky_kingdom SET name=[user input] WHERE id=[user input]

// Update Race Name
UPDATE sky_race SET name=[user input] WHERE id=[user input]

// Update Faction Name
UPDATE sky_faction SET name=[user input] WHERE id=[user input]

// Update Weapon Used
UPDATE sky_people SET weapon=[user input] WHERE first_name=[user input]AND last_name = [user input]



// Select Statements 
SELECT id, first_name, last_name FROM sky_people

SELECT id, name FROM sky_faction

SELECT id, name FROM sky_kingdom

SELECT id, name FROM sky_race

SELECT * FROM sky_people

SELECT * FROM sky_weather

SELECT sk.id AS id, sk.name AS name, sk.population AS population, sw.typical_weather AS typical_weather  
FROM sky_kingdom sk INNER JOIN sky_weather sw ON sw.id=sk.sky_weatherID

SELECT * FROM sky_race

SELECT * FROM sky_faction

SELECT sp.first_name AS fname, sp.last_name AS lname, sf.name AS name, sfk.interesting_note AS note 
FROM sky_faction_category sfk
INNER JOIN sky_people sp ON sp.id=sfk.sky_peopleID
INNER JOIN sky_faction sf ON sf.id=sfk.sky_factionID


// Delete Statements

DELETE FROM sky_race WHERE name=[user input] 
DELETE FROM sky_kingdom WHERE name=[user input] 

TRUNCATE sky_faction_category
TRUNCATE sky_people
TRUNCATE sky_faction
TRUNCATE sky_race
TRUNCATE sky_kingdom
TRUNCATE sky_weather
    
	