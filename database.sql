-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Nov 29, 2015 at 08:04 PM
-- Server version: 10.1.8-MariaDB
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
-- Table structure for table `businesses`
--

CREATE TABLE `businesses` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL,
  `Name` varchar(128) NOT NULL,
  `Type` int(11) NOT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL,
  `Interior` int(11) NOT NULL,
  `VirtualWorld` int(11) NOT NULL,
  `Locked` tinyint(1) NOT NULL DEFAULT '0',
  `Price` int(11) NOT NULL,
  `Level` tinyint(11) NOT NULL,
  `Payout` int(11) NOT NULL DEFAULT '50'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `business_types`
--

CREATE TABLE `business_types` (
  `ID` int(11) NOT NULL,
  `Name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `business_types`
--

INSERT INTO `business_types` (`ID`, `Name`) VALUES
(1, 'Bank'),
(2, 'Gun shop');

-- --------------------------------------------------------

--
-- Table structure for table `factions`
--

CREATE TABLE `factions` (
  `ID` int(11) NOT NULL,
  `Name` text NOT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `factions`
--

INSERT INTO `factions` (`ID`, `Name`, `EntranceX`, `EntranceY`, `EntranceZ`, `ExitX`, `ExitY`, `ExitZ`) VALUES
(1, 'Los Santos Police Department', 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `faction_vehicles`
--

CREATE TABLE `faction_vehicles` (
  `ID` int(11) NOT NULL,
  `OwnerID` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `houses`
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
  `Interior` int(11) NOT NULL,
  `VirtualWorld` int(11) NOT NULL,
  `Locked` tinyint(1) NOT NULL DEFAULT '0',
  `Price` int(11) NOT NULL,
  `Level` tinyint(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `players`
--

CREATE TABLE `players` (
  `ID` int(11) NOT NULL,
  `Name` varchar(24) NOT NULL,
  `Password` text NOT NULL,
  `Salt` text NOT NULL,
  `Email` text NOT NULL,
  `Pin` text NOT NULL,
  `Sex` tinyint(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `player_vehicles`
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
  ADD KEY `OwnerID` (`OwnerID`),
  ADD KEY `Type` (`Type`);

--
-- Indexes for table `business_types`
--
ALTER TABLE `business_types`
  ADD PRIMARY KEY (`ID`);

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
-- AUTO_INCREMENT for table `business_types`
--
ALTER TABLE `business_types`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
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
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `businesses`
--
ALTER TABLE `businesses`
  ADD CONSTRAINT `businesses_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT `businesses_ibfk_2` FOREIGN KEY (`Type`) REFERENCES `business_types` (`ID`) ON UPDATE CASCADE;

--
-- Constraints for table `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
  ADD CONSTRAINT `faction_vehicles_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `factions` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `houses`
--
ALTER TABLE `houses`
  ADD CONSTRAINT `houses_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
  ADD CONSTRAINT `player_vehicles_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
