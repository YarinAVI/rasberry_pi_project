#ifndef __DOG_FUNCTIONS_H__
#define __DOG_FUNCTIONS_H__

enum dog_error_code {
	//no error
	ERROR_SUCCESS = 0,
	// heap memory allocation errors
	ERROR_MEM_MALLOC_NULL,
	// arguments error
	ERROR_NULL_ARGUMENT,
	ERROR_BAD_ARGUMENTS,
};



enum dog_error_code dog_init(int argc,char **argv);
enum dog_error_code dog_show_water();
enum dog_error_code dog_show_food();
enum dog_error_code dog_help();
enum dog_error_code dog_show_status();
enum dog_error_code dog_show_all();



#endif