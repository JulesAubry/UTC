CREATE TABLE Projet (
	code SERIAL PRIMARY KEY,
	titre VARCHAR(30),
	description VARCHAR(150),
	en_avant BOOLEAN,
	p_date date,
	image1 bytea,
	image2 bytea,
	image3 bytea
);

CREATE TABLE Associe_a (
	code1 INTEGER REFERENCES Projet(code),
	code2 INTEGER REFERENCES Projet(code),
	PRIMARY KEY(code1, code2)
);

CREATE TABLE Modele_scenari (
	nom_modele INTEGER UNIQUE,
	n_vers VARCHAR(10) UNIQUE,
	PRIMARY KEY (nom_modele, n_vers)
);

CREATE TABLE Skin (
	n_skin VARCHAR(10),
	modele INTEGER NOT NULL REFERENCES Modele_scenari(nom_modele),
	version VARCHAR(10) NOT NULL REFERENCES Modele_scenari(n_vers),
	PRIMARY KEY (n_skin, modele, version)
);

CREATE TABLE Extension (
	n_extension VARCHAR(10),
	modele INTEGER NOT NULL REFERENCES Modele_scenari(nom_modele),
	version VARCHAR(10) NOT NULL REFERENCES Modele_scenari(n_vers),
	PRIMARY KEY (n_extension, modele, version)
);

CREATE TABLE Utilise ( 
	nom_modele INTEGER REFERENCES Modele_scenari(nom_modele),
	n_vers VARCHAR(10) REFERENCES Modele_scenari(n_vers),
	code INTEGER REFERENCES Projet(code),
	PRIMARY KEY (nom_modele, code)
);

CREATE TABLE Lien (
	url VARCHAR(50) PRIMARY KEY,
	code INTEGER REFERENCES Projet(code),
	type VARCHAR(1) CHECK (type = 'F' OR type = 'P')
);

CREATE TABLE Personne_morale (
	id INTEGER,
	email VARCHAR(320) UNIQUE /*REFERENCES Contact(email)*/,
	nom VARCHAR(20) NOT NULL UNIQUE,
	type VARCHAR(10)
);

CREATE SEQUENCE id_contact;

ALTER TABLE public.id_contact OWNER TO nf17a017;

ALTER SEQUENCE id_contact OWNED BY Personne_morale.id;

ALTER TABLE ONLY Personne_morale ALTER COLUMN id SET DEFAULT nextval('id_contact'::regclass);

ALTER TABLE ONLY Personne_morale
    ADD CONSTRAINT Personne_morale_pkey PRIMARY KEY (id);

CREATE TABLE Personne_physique (
	id INTEGER,
	email VARCHAR(320) UNIQUE /*REFERENCES Contact(email)*/,
	employeur INTEGER REFERENCES Personne_morale(id),
	nom VARCHAR(20) NOT NULL,
	prenom VARCHAR(20) NOT NULL,
	poste VARCHAR(50),
	UNIQUE(nom, prenom)
);

/*ALTER TABLE public.id_contact OWNER TO nf17a017;

ALTER SEQUENCE id_contact OWNED BY Personne_morale.id;*/


ALTER TABLE ONLY Personne_physique ALTER COLUMN id SET DEFAULT nextval('id_contact'::regclass);

ALTER TABLE ONLY Personne_physique
    ADD CONSTRAINT Personne_physique_pkey PRIMARY KEY (id);


CREATE TABLE A_pour_role (
	code INTEGER REFERENCES Projet(code),
	id_contact INTEGER, /* Comment mettre la référence ? */
	role VARCHAR(20),
	PRIMARY KEY (code, id_contact)
);

/* DEBUT DE L'ARCHIVAGE ------------------------------------------ */

CREATE TABLE Projet_archive (
	id SERIAL PRIMARY KEY,
	numero_archive INTEGER,
	code INTEGER NOT NULL UNIQUE,
	titre VARCHAR(30),
	description VARCHAR(50),
	en_avant BOOLEAN,
	p_date date,
	image1 bytea,
	image2 bytea,
	image3 bytea	
);

CREATE TABLE Modele_scenari_archive (
	id SERIAL PRIMARY KEY,
	numero_archive INTEGER,
	code INTEGER NOT NULL UNIQUE,
	version VARCHAR(10),
	extension VARCHAR(10)
);

CREATE TABLE Personne_physique_archive (
	id SERIAL PRIMARY KEY,
	numero_archive INTEGER,
	email VARCHAR(320) NOT NULL UNIQUE,
	nom VARCHAR(20) NOT NULL,
	prenom VARCHAR(20) NOT NULL,
	UNIQUE(nom, prenom)
);

CREATE TABLE Personne_morale_archive (
	id SERIAL PRIMARY KEY,
	numero_archive INTEGER,
	email VARCHAR(320) NOT NULL UNIQUE,
	nom VARCHAR(20) NOT NULL UNIQUE,
	type VARCHAR(10)
);