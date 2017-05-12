-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: 2017-05-12 09:16:20
-- 服务器版本： 5.7.18
-- PHP Version: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pachong`
--
CREATE DATABASE IF NOT EXISTS `pachong` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `pachong`;

-- --------------------------------------------------------

--
-- 表的结构 `essay_url`
--

DROP TABLE IF EXISTS `essay_url`;
CREATE TABLE `essay_url` (
  `uid` mediumint(8) NOT NULL,
  `url` char(255) NOT NULL,
  `title` char(200) NOT NULL DEFAULT '',
  `stat` int(1) UNSIGNED NOT NULL DEFAULT '0',
  `createtime` timestamp(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) ON UPDATE CURRENT_TIMESTAMP(6)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- 表的结构 `seed_url`
--

DROP TABLE IF EXISTS `seed_url`;
CREATE TABLE `seed_url` (
  `url` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `essay_url`
--
ALTER TABLE `essay_url`
  ADD PRIMARY KEY (`uid`),
  ADD UNIQUE KEY `url` (`url`);

--
-- Indexes for table `seed_url`
--
ALTER TABLE `seed_url`
  ADD PRIMARY KEY (`url`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `essay_url`
--
ALTER TABLE `essay_url`
  MODIFY `uid` mediumint(8) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=0;COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
