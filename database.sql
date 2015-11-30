-- phpMyAdmin SQL Dump
-- version 4.5.0.2
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 30 Noi 2015 la 17:40
-- Versiune server: 10.0.17-MariaDB
-- PHP Version: 5.6.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `sampromania`
--

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `businesses`
--

CREATE TABLE `businesses` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL,
  `Interior` tinyint(11) NOT NULL,
  `VirtualWorld` tinyint(11) NOT NULL,
  `Locked` tinyint(11) NOT NULL,
  `Price` int(11) NOT NULL,
  `Level` tinyint(11) NOT NULL,
  `Payout` int(11) NOT NULL DEFAULT '25'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `factions`
--

CREATE TABLE `factions` (
  `ID` int(11) NOT NULL,
  `Name` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `faction_vehicles`
--

CREATE TABLE `faction_vehicles` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `houses`
--

CREATE TABLE `houses` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL,
  `Interior` tinyint(11) NOT NULL,
  `VirtualWorld` tinyint(11) NOT NULL,
  `Lock` tinyint(11) NOT NULL,
  `Price` int(11) NOT NULL,
  `Level` tinyint(11) NOT NULL,
  `RentPrice` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `players`
--

CREATE TABLE `players` (
  `ID` int(11) NOT NULL,
  `Name` varchar(24) NOT NULL,
  `Password` text NOT NULL,
  `Salt` text NOT NULL,
  `Email` text NOT NULL,
  `Pin` text NOT NULL,
  `Sex` tinyint(4) NOT NULL,
  `Cash` int(11) NOT NULL DEFAULT '0',
  `Account` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Salvarea datelor din tabel `players`
--

INSERT INTO `players` (`ID`, `Name`, `Password`, `Salt`, `Email`, `Pin`, `Sex`, `Cash`, `Account`) VALUES
(1, 'WiDuAlK', 'd82eef184bd2edd4f4e37a32e48ab13a18a435b94f08e562747af987976de596', 'X6c7hcH4zkjBd8o5HgYPWWrgsn91Hfz9RV0N8C271AI4UhZtmcrsP0bDWBEU4O7GxHe7xeQ1I2kHrpntBcg5g', 'claudiu_sharingen@yahoo.com', '8e4a8b2be51350cea8db69db227ad2b54cf515c93632a49b5308bff4162eef47', 1, 0, 0);

-- --------------------------------------------------------

--
-- Structura de tabel pentru tabelul `player_vehicles`
--

CREATE TABLE `player_vehicles` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `businesses`
--
ALTER TABLE `businesses`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `OwnerID` (`OwnerID`);

--
-- Indexes for table `factions`
--
ALTER TABLE `factions`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `OwnerID` (`OwnerID`);

--
-- Indexes for table `houses`
--
ALTER TABLE `houses`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `OwnerID` (`OwnerID`);

--
-- Indexes for table `players`
--
ALTER TABLE `players`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `OwnerID` (`OwnerID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `businesses`
--
ALTER TABLE `businesses`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `houses`
--
ALTER TABLE `houses`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `players`
--
ALTER TABLE `players`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- Restrictii pentru tabele sterse
--

--
-- Restrictii pentru tabele `businesses`
--
ALTER TABLE `businesses`
  ADD CONSTRAINT `businesses_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Restrictii pentru tabele `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
  ADD CONSTRAINT `faction_vehicles_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `factions` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Restrictii pentru tabele `houses`
--
ALTER TABLE `houses`
  ADD CONSTRAINT `houses_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Restrictii pentru tabele `player_vehicles`
--
ALTER TABLE `player_vehicles`
  ADD CONSTRAINT `player_vehicles_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
