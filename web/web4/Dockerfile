FROM php:5.6-apache

COPY sources.list /etc/apt/sources.list
COPY php.ini /usr/local/etc/php/php.ini
RUN apt-get update
RUN apt-get install -y \
		libfreetype6-dev \
		libjpeg62-turbo-dev \
		libpng-dev \
	&& docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ \
	&& docker-php-ext-install -j$(nproc) gd



