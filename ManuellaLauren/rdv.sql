--------------------------------------------------------
--  Fichier créé - mercredi-décembre-04-2019   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table RDV
--------------------------------------------------------

  CREATE TABLE "MANUELLA"."RDV" 
   (	"CIN" VARCHAR2(20 BYTE), 
	"NOM" VARCHAR2(20 BYTE), 
	"PRENOM" VARCHAR2(20 BYTE), 
	"DATEE" VARCHAR2(20 BYTE), 
	"HEURE" VARCHAR2(20 BYTE), 
	"OBJET" VARCHAR2(20 BYTE), 
	"MEDECIN" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into MANUELLA.RDV
SET DEFINE OFF;
Insert into MANUELLA.RDV (CIN,NOM,PRENOM,DATEE,HEURE,OBJET,MEDECIN) values ('14574','gyity','dryds','1564','789','sejuyuoipo','ioyuret');
Insert into MANUELLA.RDV (CIN,NOM,PRENOM,DATEE,HEURE,OBJET,MEDECIN) values ('145',':c??mze','f"''''','0','14','-h-','"("''-');
Insert into MANUELLA.RDV (CIN,NOM,PRENOM,DATEE,HEURE,OBJET,MEDECIN) values ('145','jhg','hgfd','0','14','oiuytr','kjhgfd');
Insert into MANUELLA.RDV (CIN,NOM,PRENOM,DATEE,HEURE,OBJET,MEDECIN) values ('12','benee','manuella','1111','20','maladie','TCHA');
Insert into MANUELLA.RDV (CIN,NOM,PRENOM,DATEE,HEURE,OBJET,MEDECIN) values ('145','hyd','jhsy','145','14','maladie','TCHA');
--------------------------------------------------------
--  Constraints for Table RDV
--------------------------------------------------------

  ALTER TABLE "MANUELLA"."RDV" MODIFY ("CIN" NOT NULL ENABLE);
