#!/bin/bash
mysqld_safe &
echo -n "Waiting for mysql startup"
while ! mysqladmin --host="localhost" --silent ping ; do
    echo -n "."
    sleep 1
done
echo

mysql -uroot <<EOF
UPDATE mysql.user SET Password=PASSWORD('nuAaCtF_skrrrrR'), plugin = '' WHERE User='root';
create database web1;
use web1;
CREATE TABLE users (
  username varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  password varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  id int(11) NOT NULL AUTO_INCREMENT,
  is_admin tinyint(32) NOT NULL,
  email varchar(32) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY username (username)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
BEGIN;
INSERT INTO users VALUES ('admin', 'a07eb6555b03258d129aba49a11587bc', 1, 1, 'zeddyu_lu@qq.com');
INSERT INTO users VALUES ('admin1', 'a07eb6555b03258d129aba49a11587bc', 2, 1, 'zeddyu_lu@qq.com');
INSERT INTO users VALUES ('admin2', 'a07eb6555b03258d129aba49a11587bc', 3, 1, 'zeddyu_lu@qq.com');
INSERT INTO users VALUES ('admin3', 'a07eb6555b03258d129aba49a11587bc', 4, 1, 'zeddyu_lu@qq.com');
INSERT INTO users VALUES ('admin4', 'a07eb6555b03258d129aba49a11587bc', 5, 1, 'zeddyu_lu@qq.com');
COMMIT;
SET FOREIGN_KEY_CHECKS = 1;
CREATE USER 'nuaactf'@'localhost' IDENTIFIED BY 'nuaaCTF';
update mysql.user set plugin='mysql_native_password' where user='nuaactf';
GRANT ALL ON web1.* TO 'nuaactf'@'localhost';
FLUSH PRIVILEGES;

EOF

mysqladmin -uroot -pnuAaCtF_skrrrrR shutdown