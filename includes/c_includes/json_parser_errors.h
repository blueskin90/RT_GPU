/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser_errors.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <toliver@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:51:57 by cvermand          #+#    #+#             */
/*   Updated: 2019/02/11 05:37:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_ERRORS_H
# define JSON_PARSER_ERRORS_H

/*
** FILE OPEN READ WRITE ERRORS
*/

# define FD_FAIL "Could not open file\n"
# define EMPTY_FILE	"file is empty\n"
# define END_OF_FILE_BAD_FORMAT "Too much caracters at end of file\n"

/*
** ERROR PARSING
*/

# define JSON_PARSING_ERROR "JSON HAS WRONG FORMAT\n"
# define KEY_NOT_FOUND "KEY WAS NOT RECOGNIZED\n"
# define NO_CLOSING_BRACKETS "NO CLOSING BRACKETS\n"
# define VALUE_NOT_RECOGNIZED "VALUE COULD NOT BE RECOGNIZED\n"
# define UNEXPECTED_END_OF_FILE "FILE ENDED TO SOON\n"
# define ARRAY_BAD_FORMAT "ARRAY HAS NO CLOSING BRACKET\n"
# define ARRAY_MULTIPLE_TYPE "ARRAY MUST CONTAIN ONLY ONE TYPE\n"
# define OBJECT_BAD_FORMAT "OBJECT HAS NO CLOSING BRACKET\n"
# define SAME_KEY_NAME "ONE OBJECT HAS DUPLICATE KEY\n"
# define BAD_BEGIN_OF_FILE "JSON FILE MUST BEGIN WITH [ or {\n"
# define STRING_TO_LONG "STRING MUST BE SMALLER THAN MAX_INT\n"
# define KEY_TO_LONG "KEY MUST BE SMALLER THAN MAX_INT\n"

#endif
