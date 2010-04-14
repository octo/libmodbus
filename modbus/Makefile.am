lib_LTLIBRARIES = libmodbus.la
libmodbus_la_SOURCES = modbus.c modbus.h version.h
libmodbus_la_LDFLAGS = -version-info @LIBMODBUS_CURRENT@:@LIBMODBUS_REVISION@:@LIBMODBUS_AGE@
service_CFLAGS = -I$(top_srcdir)/

# Include files to install
libmodbusincludedir = $(includedir)/modbus
libmodbusinclude_HEADERS = modbus.h

CLEANFILES = *~
