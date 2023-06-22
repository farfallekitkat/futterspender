-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server Version:               8.0.31 - MySQL Community Server - GPL
-- Server Betriebssystem:        Win64
-- HeidiSQL Version:             11.3.0.6295
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Exportiere Datenbank Struktur für futterspender
DROP DATABASE IF EXISTS `futterspender`;
CREATE DATABASE IF NOT EXISTS `futterspender` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `futterspender`;

-- Exportiere Struktur von Tabelle futterspender.ausgaben
DROP TABLE IF EXISTS `ausgaben`;
CREATE TABLE IF NOT EXISTS `ausgaben` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `fa_ID` int DEFAULT NULL,
  `cat_ID` int DEFAULT NULL,
  `Uhrzeit` time DEFAULT NULL,
  `Datum` date DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `FK_ausgaben_festeausgabe` (`fa_ID`),
  KEY `FK_ausgaben_katze` (`cat_ID`),
  CONSTRAINT `FK_ausgaben_festeausgabe` FOREIGN KEY (`fa_ID`) REFERENCES `festeausgabe` (`ID`),
  CONSTRAINT `FK_ausgaben_katze` FOREIGN KEY (`cat_ID`) REFERENCES `katze` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Speicherung der Daten wann immer Essen ausgegeben wurde. \r\nWenn Essen an den vorher gespeicherten Werten ausgegeben wurde, wird nur die fa_ID (festeausgabe ID) und das heutige Datum gefüllt. \r\n\r\nWenn eine Katze für die Ausgabe verantwortlich ist durch RFID, wird cat_ID, Uhrzeit und das heutige Datum gefüllt. ';

-- Exportiere Daten aus Tabelle futterspender.ausgaben: ~0 rows (ungefähr)
DELETE FROM `ausgaben`;
/*!40000 ALTER TABLE `ausgaben` DISABLE KEYS */;
/*!40000 ALTER TABLE `ausgaben` ENABLE KEYS */;

-- Exportiere Struktur von Tabelle futterspender.festeausgabe
DROP TABLE IF EXISTS `festeausgabe`;
CREATE TABLE IF NOT EXISTS `festeausgabe` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Uhrzeit` time NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Allgemeine Essensausgabe zu festen Zeiten \r\n';

-- Exportiere Daten aus Tabelle futterspender.festeausgabe: ~3 rows (ungefähr)
DELETE FROM `festeausgabe`;
/*!40000 ALTER TABLE `festeausgabe` DISABLE KEYS */;
INSERT INTO `festeausgabe` (`ID`, `Uhrzeit`) VALUES
	(1, '02:56:37'),
	(11, '00:00:00'),
	(12, '02:02:00');
/*!40000 ALTER TABLE `festeausgabe` ENABLE KEYS */;

-- Exportiere Struktur von Tabelle futterspender.katze
DROP TABLE IF EXISTS `katze`;
CREATE TABLE IF NOT EXISTS `katze` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) COLLATE utf8mb4_general_ci NOT NULL DEFAULT '0',
  `maxFutterausgabe` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Daten der Katzen';

-- Exportiere Daten aus Tabelle futterspender.katze: ~2 rows (ungefähr)
DELETE FROM `katze`;
/*!40000 ALTER TABLE `katze` DISABLE KEYS */;
INSERT INTO `katze` (`ID`, `Name`, `maxFutterausgabe`) VALUES
	(1, 'Tom', 5),
	(2, 'Y', 2);
/*!40000 ALTER TABLE `katze` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
