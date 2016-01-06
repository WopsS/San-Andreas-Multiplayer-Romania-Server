-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 06, 2016 at 11:32 AM
-- Server version: 5.5.46-0+deb8u1
-- PHP Version: 5.6.14-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sampro_server`
--

-- --------------------------------------------------------

--
-- Table structure for table `businesses`
--

CREATE TABLE IF NOT EXISTS `businesses` (
`ID` smallint(5) unsigned NOT NULL,
  `OwnerID` bigint(20) unsigned DEFAULT NULL,
  `Name` varchar(128) NOT NULL,
  `Type` tinyint(3) unsigned DEFAULT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL,
  `Interior` tinyint(3) unsigned NOT NULL,
  `VirtualWorld` int(10) unsigned NOT NULL,
  `Locked` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `Price` int(10) unsigned NOT NULL,
  `Level` tinyint(3) unsigned NOT NULL,
  `Payout` int(10) unsigned NOT NULL DEFAULT '25'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `business_types`
--

CREATE TABLE IF NOT EXISTS `business_types` (
`ID` tinyint(3) unsigned NOT NULL,
  `Name` varchar(64) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

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

CREATE TABLE IF NOT EXISTS `factions` (
`ID` smallint(5) unsigned NOT NULL,
  `Name` text NOT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `factions`
--

INSERT INTO `factions` (`ID`, `Name`, `EntranceX`, `EntranceY`, `EntranceZ`, `ExitX`, `ExitY`, `ExitZ`) VALUES
(1, 'Los Santos Police Department', 1, 2, 3, 4, 5, 6),
(2, 'Las Venturas Police Department', 0, 0, 0, 0, 0, 0),
(3, 'Firemen & Paramedics', 0, 0, 0, 0, 0, 0),
(5, 'San Fiero Police Department', 0, 0, 0, 0, 0, 0),
(6, 'Taxi Company', 0, 0, 0, 0, 0, 0),
(7, 'News Reporters', 0, 0, 0, 0, 0, 0),
(8, 'National Guard', 0, 0, 0, 0, 0, 0),
(9, 'Hitman Agency', 0, 0, 0, 0, 0, 0),
(10, 'School Instructors', 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `faction_vehicles`
--

CREATE TABLE IF NOT EXISTS `faction_vehicles` (
`ID` bigint(20) unsigned NOT NULL,
  `OwnerID` smallint(5) unsigned DEFAULT NULL,
  `Model` smallint(5) unsigned NOT NULL,
  `X` int(11) NOT NULL,
  `Y` int(11) NOT NULL,
  `Z` int(11) NOT NULL,
  `Rotation` float NOT NULL,
  `Color1` tinyint(3) unsigned NOT NULL,
  `Color2` tinyint(3) unsigned NOT NULL,
  `RespawnTime` int(10) unsigned NOT NULL,
  `Siren` tinyint(3) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB AUTO_INCREMENT=225 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `faction_vehicles`
--

INSERT INTO `faction_vehicles` (`ID`, `OwnerID`, `Model`, `X`, `Y`, `Z`, `Rotation`, `Color1`, `Color2`, `RespawnTime`, `Siren`) VALUES
(1, 1, 523, 1595, -1710, 6, 0, 0, 1, 60, 0),
(2, 1, 523, 1591, -1710, 6, 0, 0, 1, 60, 0),
(3, 1, 523, 1587, -1710, 6, 0, 0, 1, 60, 0),
(4, 1, 596, 1578, -1710, 6, 0, 0, 1, 60, 0),
(5, 1, 596, 1574, -1710, 6, 0, 0, 1, 60, 0),
(6, 1, 596, 1570, -1710, 6, 0, 0, 1, 60, 0),
(7, 1, 596, 1559, -1710, 6, 0, 0, 1, 60, 0),
(8, 1, 523, 1529, -1688, 6, 269, 0, 1, 60, 0),
(9, 1, 523, 1529, -1684, 6, 269, 0, 1, 60, 0),
(10, 1, 427, 1545, -1684, 6, 90, 0, 1, 60, 0),
(11, 1, 427, 1545, -1680, 6, 90, 0, 1, 60, 0),
(12, 1, 427, 1545, -1676, 6, 90, 0, 1, 60, 0),
(13, 1, 427, 1545, -1672, 6, 90, 0, 1, 60, 0),
(14, 1, 601, 1545, -1663, 6, 90, 0, 1, 60, 0),
(15, 1, 601, 1545, -1659, 6, 90, 0, 1, 60, 0),
(16, 1, 601, 1545, -1655, 6, 90, 0, 1, 60, 0),
(17, 1, 601, 1545, -1651, 6, 90, 0, 1, 60, 0),
(18, 1, 541, 1539, -1645, 6, 180, 0, 1, 60, 0),
(19, 1, 541, 1535, -1645, 6, 180, 0, 1, 60, 0),
(20, 1, 411, 1531, -1645, 6, 180, 0, 1, 60, 0),
(21, 1, 411, 1527, -1645, 6, 180, 0, 1, 60, 0),
(22, 1, 596, 1602, -1684, 5, 90, 0, 1, 60, 0),
(23, 1, 596, 1602, -1688, 5, 90, 0, 1, 60, 0),
(24, 1, 596, 1602, -1692, 5, 90, 0, 1, 60, 0),
(25, 1, 596, 1602, -1696, 5, 90, 0, 1, 60, 0),
(26, 1, 596, 1602, -1700, 5, 90, 0, 1, 60, 0),
(27, 1, 596, 1602, -1704, 5, 90, 0, 1, 60, 0),
(28, 1, 596, 1536, -1678, 13, 0, 0, 1, 60, 0),
(29, 1, 596, 1536, -1667, 13, 180, 0, 1, 60, 0),
(30, 3, 416, -2571, 657, 15, 270, 1, 3, 60, 0),
(31, 3, 416, -2571, 647, 15, 270, 1, 3, 60, 0),
(32, 3, 416, -2571, 632, 15, 270, 1, 3, 60, 0),
(33, 3, 416, -2571, 622, 15, 270, 1, 3, 60, 0),
(34, 3, 416, -2588, 622, 15, 270, 1, 3, 60, 0),
(35, 3, 416, -2588, 627, 15, 270, 1, 3, 60, 0),
(36, 3, 416, -2588, 632, 15, 270, 1, 3, 60, 0),
(37, 3, 416, -2588, 637, 15, 270, 1, 3, 60, 0),
(38, 3, 416, -2546, 622, 15, 90, 1, 3, 60, 0),
(39, 3, 416, -2546, 627, 15, 90, 1, 3, 60, 0),
(40, 3, 416, -2546, 632, 15, 90, 1, 3, 60, 0),
(41, 3, 416, -2546, 637, 15, 90, 1, 3, 60, 0),
(42, 3, 599, -2543, 587, 15, 90, 1, 3, 60, 0),
(43, 3, 599, -2543, 592, 15, 90, 1, 3, 60, 0),
(44, 3, 599, -2543, 598, 15, 90, 1, 3, 60, 0),
(45, 3, 599, -2543, 604, 15, 90, 1, 3, 60, 0),
(46, 3, 599, -2543, 610, 15, 90, 1, 3, 60, 0),
(47, 3, 599, -2545, 658, 15, 90, 1, 3, 60, 0),
(48, 3, 599, -2545, 652, 15, 90, 1, 3, 60, 0),
(49, 3, 599, -2545, 647, 15, 90, 1, 3, 60, 0),
(50, 3, 599, -2589, 658, 15, 269, 1, 3, 60, 0),
(51, 3, 599, -2589, 652, 15, 269, 1, 3, 60, 0),
(52, 3, 599, -2589, 647, 15, 269, 1, 3, 60, 0),
(53, 3, 599, -2552, 626, 28, 0, 1, 3, 60, 0),
(54, 3, 599, -2557, 626, 28, 0, 1, 3, 60, 0),
(55, 3, 599, -2563, 626, 28, 0, 1, 3, 60, 0),
(56, 3, 599, -2568, 626, 28, 0, 1, 3, 60, 0),
(57, 3, 599, -2573, 626, 28, 0, 1, 3, 60, 0),
(58, 3, 599, -2578, 626, 28, 0, 1, 3, 60, 0),
(59, 3, 599, -2583, 626, 28, 0, 1, 3, 60, 0),
(60, 3, 487, -2557, 653, 28, 180, 1, 3, 60, 0),
(61, 3, 487, -2569, 653, 28, 180, 1, 3, 60, 0),
(62, 3, 487, -2581, 653, 28, 180, 1, 3, 60, 0),
(63, 2, 523, 2252, 2475, 11, 180, 0, 0, 60, 0),
(64, 2, 523, 2256, 2475, 11, 180, 0, 0, 60, 0),
(65, 2, 523, 2260, 2475, 11, 180, 0, 0, 60, 0),
(66, 2, 601, 2282, 2477, 11, 180, 1, 1, 60, 0),
(67, 2, 601, 2278, 2477, 11, 180, 1, 1, 60, 0),
(68, 2, 601, 2273, 2477, 11, 180, 1, 1, 60, 0),
(69, 2, 601, 2269, 2477, 11, 180, 1, 1, 60, 0),
(70, 2, 541, 2290, 2477, 11, 180, 0, 1, 60, 0),
(71, 2, 541, 2295, 2477, 11, 180, 0, 1, 60, 0),
(72, 2, 411, 2295, 2443, 11, 360, 0, 1, 60, 0),
(73, 2, 411, 2290, 2443, 11, 360, 0, 1, 60, 0),
(74, 2, 427, 2282, 2443, 11, 0, 0, 0, 60, 0),
(75, 2, 427, 2278, 2443, 11, 0, 0, 0, 60, 0),
(76, 2, 427, 2273, 2443, 11, 0, 0, 0, 60, 0),
(77, 2, 427, 2269, 2443, 11, 0, 0, 0, 60, 0),
(78, 2, 523, 2260, 2443, 11, 0, 0, 1, 60, 0),
(79, 2, 523, 2256, 2443, 11, 0, 0, 1, 60, 0),
(80, 2, 523, 2252, 2443, 11, 0, 0, 1, 60, 0),
(81, 2, 598, 2282, 2459, 11, 180, 0, 1, 60, 0),
(82, 2, 598, 2277, 2459, 11, 180, 0, 1, 60, 0),
(83, 2, 598, 2273, 2459, 11, 180, 0, 1, 60, 0),
(84, 2, 598, 2269, 2459, 11, 180, 0, 1, 60, 0),
(85, 2, 598, 2260, 2459, 11, 180, 0, 1, 60, 0),
(86, 2, 598, 2256, 2459, 11, 180, 0, 1, 60, 0),
(87, 2, 598, 2252, 2459, 11, 180, 0, 1, 60, 0),
(88, 1, 497, 1566, -1706, 29, 90, 0, 1, 60, 0),
(89, 1, 497, 1572, -1644, 29, 180, 0, 1, 60, 0),
(90, 1, 497, 1555, -1644, 29, 180, 0, 1, 60, 0),
(91, 2, 497, 2291, 2472, 39, 0, 0, 1, 60, 0),
(92, 2, 497, 2277, 2472, 39, 0, 0, 1, 60, 0),
(93, 2, 497, 2263, 2472, 39, 0, 0, 1, 60, 0),
(94, 5, 497, -1679, 705, 31, 90, 0, 1, 60, 0),
(95, 5, 597, -1608, 748, -6, 180, 0, 1, 60, 0),
(96, 5, 597, -1604, 748, -6, 180, 0, 1, 60, 0),
(97, 5, 597, -1600, 748, -6, 180, 0, 1, 60, 0),
(98, 5, 597, -1596, 748, -6, 180, 0, 1, 60, 0),
(99, 5, 597, -1592, 748, -6, 180, 0, 1, 60, 0),
(100, 5, 597, -1588, 748, -6, 180, 0, 1, 60, 0),
(101, 5, 597, -1584, 748, -6, 180, 0, 1, 60, 0),
(102, 5, 597, -1580, 748, -6, 180, 0, 1, 60, 0),
(103, 5, 523, -1612, 734, -6, 0, 0, 0, 60, 0),
(104, 5, 523, -1616, 734, -6, 0, 0, 0, 60, 0),
(105, 5, 597, -1573, 742, -5, 90, 0, 1, 60, 0),
(106, 5, 597, -1573, 738, -5, 90, 0, 1, 60, 0),
(107, 5, 597, -1573, 734, -5, 90, 0, 1, 60, 0),
(108, 5, 597, -1573, 730, -5, 90, 0, 1, 60, 0),
(109, 5, 597, -1573, 726, -5, 90, 0, 1, 60, 0),
(110, 5, 523, -1573, 722, -5, 90, 0, 1, 60, 0),
(111, 5, 523, -1573, 718, -5, 90, 0, 1, 60, 0),
(112, 5, 523, -1573, 714, -5, 90, 0, 1, 60, 0),
(113, 5, 523, -1573, 710, -5, 90, 0, 1, 60, 0),
(114, 5, 523, -1573, 706, -5, 90, 0, 1, 60, 0),
(115, 5, 597, -1600, 676, -5, 0, 0, 1, 60, 0),
(116, 5, 597, -1596, 676, -5, 0, 0, 1, 60, 0),
(117, 5, 411, -1600, 693, -6, 180, 0, 1, 60, 0),
(118, 5, 411, -1604, 693, -6, 180, 0, 1, 60, 0),
(119, 5, 411, -1608, 693, -6, 180, 0, 1, 60, 0),
(120, 5, 599, -1612, 692, -6, 180, 0, 1, 60, 0),
(121, 5, 599, -1616, 692, -6, 180, 0, 1, 60, 0),
(122, 5, 599, -1620, 692, -6, 180, 0, 1, 60, 0),
(123, 5, 541, -1624, 692, -5, 180, 0, 1, 60, 0),
(124, 5, 541, -1628, 692, -5, 180, 0, 1, 60, 0),
(125, 5, 541, -1632, 692, -5, 180, 0, 1, 60, 0),
(126, 5, 599, -1639, 682, -5, 270, 0, 1, 60, 0),
(127, 5, 599, -1639, 678, -5, 270, 0, 1, 60, 0),
(128, 5, 599, -1639, 674, -5, 270, 0, 1, 60, 0),
(129, 3, 407, 1770, 2077, 11, 180, 3, 1, 60, 0),
(130, 3, 407, 1763, 2077, 11, 180, 3, 1, 60, 0),
(131, 3, 407, 1757, 2077, 11, 180, 3, 1, 60, 0),
(132, 3, 407, 1750, 2077, 11, 180, 3, 1, 60, 0),
(133, 3, 407, 1743, 2077, 11, 180, 3, 1, 60, 0),
(134, 3, 544, 1743, 2067, 11, 255, 3, 1, 60, 0),
(135, 6, 438, 967, 1756, 8, 180, 6, 1, 60, 0),
(136, 6, 438, 963, 1756, 8, 180, 6, 1, 60, 0),
(137, 6, 438, 959, 1756, 8, 180, 6, 1, 60, 0),
(138, 6, 438, 955, 1756, 8, 180, 6, 1, 60, 0),
(139, 6, 420, 967, 1710, 8, 0, 6, 1, 60, 0),
(140, 6, 420, 963, 1710, 8, 0, 6, 1, 60, 0),
(141, 6, 420, 959, 1710, 8, 0, 6, 1, 60, 0),
(142, 6, 420, 955, 1710, 8, 0, 6, 1, 60, 0),
(143, 6, 420, 984, 1723, 9, 90, 6, 1, 60, 0),
(144, 6, 420, 984, 1727, 9, 90, 6, 1, 60, 0),
(145, 6, 420, 984, 1731, 9, 90, 6, 1, 60, 0),
(146, 6, 438, 983, 1735, 9, 90, 6, 76, 60, 0),
(147, 6, 438, 983, 1739, 9, 90, 6, 76, 60, 0),
(148, 6, 438, 983, 1743, 9, 90, 6, 76, 60, 0),
(149, 6, 438, 952, 1741, 9, 270, 6, 76, 60, 0),
(150, 6, 438, 952, 1745, 9, 270, 6, 76, 60, 0),
(151, 6, 438, 952, 1749, 9, 270, 6, 76, 60, 0),
(152, 6, 420, 952, 1725, 8, 270, 6, 1, 60, 0),
(153, 6, 420, 952, 1721, 8, 270, 6, 1, 60, 0),
(154, 6, 420, 952, 1717, 8, 270, 6, 1, 60, 0),
(155, 7, 582, -346, 1514, 75, 0, 2, 1, 60, 0),
(156, 7, 582, -340, 1514, 75, 0, 2, 1, 60, 0),
(157, 7, 582, -334, 1514, 75, 0, 2, 1, 60, 0),
(158, 7, 582, -328, 1514, 75, 0, 2, 1, 60, 0),
(159, 7, 582, -322, 1514, 75, 0, 2, 1, 60, 0),
(160, 7, 582, -316, 1514, 75, 0, 2, 1, 60, 0),
(161, 7, 582, -265, 1542, 75, 134, 2, 1, 60, 0),
(162, 7, 582, -270, 1547, 75, 134, 2, 1, 60, 0),
(163, 7, 582, -275, 1552, 75, 135, 2, 1, 60, 0),
(164, 7, 582, -280, 1557, 75, 135, 2, 1, 60, 0),
(165, 7, 582, -285, 1562, 75, 135, 2, 1, 60, 0),
(166, 7, 582, -290, 1567, 75, 135, 2, 1, 60, 0),
(167, 7, 582, -295, 1572, 75, 135, 2, 1, 60, 0),
(168, 7, 582, -300, 1576, 75, 135, 2, 1, 60, 0),
(169, 7, 582, -305, 1582, 75, 135, 2, 1, 60, 0),
(170, 7, 488, -325, 1561, 76, 302, 2, 1, 60, 0),
(171, 7, 488, -363, 1550, 76, 179, 2, 1, 60, 0),
(172, 8, 470, 198, 1876, 18, 0, 43, 0, 60, 0),
(173, 8, 470, 203, 1876, 18, 0, 43, 0, 60, 0),
(174, 8, 470, 223, 1876, 18, 0, 43, 0, 60, 0),
(175, 8, 470, 228, 1876, 18, 0, 43, 0, 60, 0),
(176, 8, 470, 223, 1919, 18, 180, 43, 0, 60, 0),
(177, 8, 470, 218, 1919, 18, 180, 43, 0, 60, 0),
(178, 8, 470, 213, 1919, 18, 180, 43, 0, 60, 0),
(179, 8, 470, 208, 1919, 18, 180, 43, 0, 60, 0),
(180, 8, 470, 203, 1919, 18, 180, 43, 0, 60, 0),
(181, 8, 470, 198, 1919, 18, 180, 43, 0, 60, 0),
(182, 8, 470, 193, 1919, 18, 180, 43, 0, 60, 0),
(183, 8, 433, 130, 1836, 17, 90, 43, 0, 60, 0),
(184, 8, 433, 130, 1843, 17, 90, 43, 0, 60, 0),
(185, 8, 433, 130, 1850, 17, 90, 43, 0, 60, 0),
(186, 8, 433, 130, 1857, 17, 90, 43, 0, 60, 0),
(187, 8, 433, 130, 1864, 17, 90, 43, 0, 60, 0),
(188, 8, 432, 220, 1960, 17, 270, 0, 0, 60, 0),
(189, 8, 432, 220, 1992, 17, 270, 0, 0, 60, 0),
(190, 8, 432, 220, 2024, 17, 270, 0, 0, 60, 0),
(191, 8, 425, 344, 1923, 18, 90, 0, 0, 60, 0),
(192, 8, 425, 344, 1955, 18, 90, 0, 0, 60, 0),
(193, 8, 425, 344, 1987, 18, 90, 0, 0, 60, 0),
(194, 8, 520, 277, 1955, 18, 270, 0, 0, 60, 0),
(195, 8, 520, 277, 1990, 18, 270, 0, 0, 60, 0),
(196, 8, 520, 277, 2025, 18, 270, 0, 0, 60, 0),
(197, 9, 480, 1067, -293, 74, 180, 0, 0, 60, 0),
(198, 9, 480, 1071, -293, 74, 180, 0, 0, 60, 0),
(199, 9, 480, 1074, -293, 74, 180, 0, 0, 60, 0),
(200, 9, 480, 1078, -293, 74, 180, 0, 0, 60, 0),
(201, 9, 579, 1083, -287, 74, 180, 0, 0, 60, 0),
(202, 9, 579, 1088, -287, 74, 180, 0, 0, 60, 0),
(203, 9, 579, 1056, -287, 74, 180, 0, 0, 60, 0),
(204, 9, 579, 1061, -287, 74, 180, 0, 0, 60, 0),
(205, 9, 487, 1110, -336, 74, 90, 0, 0, 60, 0),
(206, 9, 487, 1110, -346, 74, 90, 0, 0, 60, 0),
(207, 9, 468, 1089, -316, 74, 90, 0, 0, 60, 0),
(208, 9, 468, 1089, -319, 74, 90, 0, 0, 60, 0),
(209, 9, 468, 1089, -322, 74, 90, 0, 0, 60, 0),
(210, 9, 468, 1089, -325, 74, 90, 0, 0, 60, 0),
(211, 9, 468, 1089, -313, 74, 90, 0, 0, 60, 0),
(212, 9, 468, 1089, -328, 74, 90, 0, 0, 60, 0),
(213, 10, 405, -2064, -83, 35, 180, 103, 103, 60, 0),
(214, 10, 405, -2068, -83, 35, 180, 103, 103, 60, 0),
(215, 10, 405, -2072, -83, 35, 180, 103, 103, 60, 0),
(216, 10, 405, -2076, -83, 35, 180, 103, 103, 60, 0),
(217, 10, 405, -2081, -83, 35, 180, 103, 103, 60, 0),
(218, 10, 405, -2085, -83, 35, 180, 103, 103, 60, 0),
(219, 10, 405, -2089, -83, 35, 180, 103, 103, 60, 0),
(220, 10, 405, -2093, -83, 35, 180, 103, 103, 60, 0);

-- --------------------------------------------------------

--
-- Table structure for table `houses`
--

CREATE TABLE IF NOT EXISTS `houses` (
`ID` smallint(5) unsigned NOT NULL,
  `OwnerID` bigint(20) unsigned DEFAULT NULL,
  `EntranceX` float NOT NULL,
  `EntranceY` float NOT NULL,
  `EntranceZ` float NOT NULL,
  `ExitX` float NOT NULL,
  `ExitY` float NOT NULL,
  `ExitZ` float NOT NULL,
  `Interior` tinyint(3) unsigned NOT NULL,
  `VirtualWorld` int(10) unsigned NOT NULL,
  `Locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Price` int(10) unsigned NOT NULL,
  `Level` tinyint(3) unsigned NOT NULL,
  `RentPrice` smallint(5) unsigned NOT NULL DEFAULT '25'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `players`
--

CREATE TABLE IF NOT EXISTS `players` (
`ID` bigint(20) unsigned NOT NULL,
  `Name` varchar(24) NOT NULL,
  `Password` text NOT NULL,
  `Salt` text NOT NULL,
  `Email` text NOT NULL,
  `Pin` text NOT NULL,
  `Sex` tinyint(3) unsigned NOT NULL,
  `AdminLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `Cash` int(11) NOT NULL DEFAULT '0',
  `Money` bigint(20) NOT NULL DEFAULT '0' COMMENT 'Money in bank.'
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `players`
--

INSERT INTO `players` (`ID`, `Name`, `Password`, `Salt`, `Email`, `Pin`, `Sex`, `AdminLevel`, `Cash`, `Money`) VALUES
(1, 'WopsS', '49b344911b2904f00e866e66d042b8f22b53cf7d078d73ab9230cecc6e2c6b4a', 'g6SJxOZnIjU749CsHbO1hvQAUkEc1MLwWyAYdz0AefWvqkc5GQUJYuT5qEvM3xiX0zgsfbbiCtQZ', 'wopss.wopss@yahoo.com', '8a4a763c69b735610b9f660544664ab32fce1a154eb3ffda2e723e38b986fd07', 1, 0, 0, 0),
(2, 'Famous', '25cec8b959afd0a5059f402cb0e051b53060901428963bcc450fe4d783923ff3', 'gFxzV1znZijjfmT1PWdOqonTTjsjrrchMr7pxslwqZk2PUPrllNBSIR4VsHXUaOs251qHYoVX6QGApqxxCO4tkouM5', 'catalin_crainic@yahoo.com', '7d3173af6ddf7c4e40d5c6d6a716beacfcf35675c9d9abf6c357f44ac378ffcf', 1, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `player_vehicles`
--

CREATE TABLE IF NOT EXISTS `player_vehicles` (
`ID` bigint(20) unsigned NOT NULL,
  `OwnerID` bigint(20) unsigned DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `businesses`
--
ALTER TABLE `businesses`
 ADD PRIMARY KEY (`ID`), ADD KEY `OwnerID` (`OwnerID`), ADD KEY `Type` (`Type`);

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
 ADD PRIMARY KEY (`ID`), ADD KEY `OwnerID` (`OwnerID`);

--
-- Indexes for table `houses`
--
ALTER TABLE `houses`
 ADD PRIMARY KEY (`ID`), ADD KEY `OwnerID` (`OwnerID`);

--
-- Indexes for table `players`
--
ALTER TABLE `players`
 ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
 ADD PRIMARY KEY (`ID`), ADD KEY `OwnerID` (`OwnerID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `businesses`
--
ALTER TABLE `businesses`
MODIFY `ID` smallint(5) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `business_types`
--
ALTER TABLE `business_types`
MODIFY `ID` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
MODIFY `ID` smallint(5) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=11;
--
-- AUTO_INCREMENT for table `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
MODIFY `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=225;
--
-- AUTO_INCREMENT for table `houses`
--
ALTER TABLE `houses`
MODIFY `ID` smallint(5) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `players`
--
ALTER TABLE `players`
MODIFY `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `player_vehicles`
--
ALTER TABLE `player_vehicles`
MODIFY `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `businesses`
--
ALTER TABLE `businesses`
ADD CONSTRAINT `businesses_ibfk_2` FOREIGN KEY (`Type`) REFERENCES `business_types` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE,
ADD CONSTRAINT `businesses_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `players` (`ID`) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `faction_vehicles`
--
ALTER TABLE `faction_vehicles`
ADD CONSTRAINT `faction_vehicles_ibfk_1` FOREIGN KEY (`OwnerID`) REFERENCES `factions` (`ID`) ON UPDATE CASCADE;

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
