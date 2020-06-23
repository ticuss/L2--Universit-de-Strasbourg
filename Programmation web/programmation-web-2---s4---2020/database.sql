-- phpMyAdmin SQL Dump
-- version 4.9.5deb1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 16, 2020 at 12:31 AM
-- Server version: 8.0.20-0ubuntu0.19.10.1
-- PHP Version: 7.3.11-0ubuntu0.19.10.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `database`
--

-- --------------------------------------------------------

--
-- Table structure for table `Eveniments`
--

CREATE TABLE `Eveniments` (
  `id` int NOT NULL,
  `title` varchar(255) NOT NULL,
  `date` date DEFAULT NULL,
  `hour` time DEFAULT NULL,
  `category` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `desciption` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `img_dest` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dumping data for table `Eveniments`
--

INSERT INTO `Eveniments` (`id`, `title`, `date`, `hour`, `category`, `desciption`, `created_at`, `img_dest`) VALUES
(52, 'Soiree a Strasbourg  EXEMPLE', NULL, NULL, NULL, 'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut \r\n                labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris\r\n                 nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit \r\n                 esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in\r\n                  culpa qui officia deserunt mollit anim id est laborum.Lorem ipsum dolor sit amet, consectetur adipiscing\r\n                   elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis \r\n                   nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in \r\n                   reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat\r\n                    non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.Lorem ipsum dolor sit amet, consectetur\r\n                     adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis\r\n                      nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit \r\n                      in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt \r\n                      in culpa qui officia deserunt mollit anim id ', '2020-05-15 21:31:52', 'assets/images/5ebf0a48826b68.65094956.jpg'),
(55, 'Soiree de fin de semestre', NULL, NULL, NULL, 'Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Nunc sed velit dignissim sodales ut eu. Sed odio morbi quis commodo odio aenean sed adipiscing diam. Viverra suspendisse potenti nullam ac tortor vitae purus. Sed viverra ipsum nunc aliquet. Donec massa sapien faucibus et molestie ac. Consectetur adipiscing elit duis tristique sollicitudin nibh. Cursus euismod quis viverra nibh cras pulvinar mattis nunc. Massa ultricies mi quis hendrerit dolor magna eget est lorem. Vitae purus faucibus ornare suspendisse sed nisi lacus. Posuere morbi leo urna molestie at. Sodales ut eu sem integer vitae justo eget magna. Fames ac turpis egestas integer eget aliquet nibh. Quam quisque id diam vel. Libero volutpat sed cras ornare. Tempor commodo ullamcorper a lacus. Turpis egestas integer eget aliquet. In hac habitasse platea dictumst vestibulum rhoncus est. Vulputate mi sit amet mauris commodo quis imperdiet massa tincidunt.\r\n\r\nFeugiat nibh sed pulvinar proin gravida. Leo in vitae turpis massa. Sagittis id consectetur purus ut faucibus pulvinar elementum integer enim. ', '2020-05-15 22:29:16', 'assets/images/5ebf17bcb0b4b8.66769303.jpg');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Eveniments`
--
ALTER TABLE `Eveniments`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Eveniments`
--
ALTER TABLE `Eveniments`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=56;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
