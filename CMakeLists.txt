cmake_minimum_required(VERSION 3.25)

project(VPNbeta)

set(SOURCE_EXE main.c)			# Установка переменной со списком исходников

include_directories(libc libc/include libc/interface_info/include libc/analizator_kernel/include)			# Расположение заголовочных файлов

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(libc)				# Добавление подпроекта, указывается имя дирректории

target_link_libraries(main library)		# Линковка программы с библиотекой