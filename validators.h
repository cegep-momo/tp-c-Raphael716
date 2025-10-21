#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>

bool isValidISBN(const std::string& isbn);
bool isValidName(const std::string& name);
bool isValidUserId(const std::string& userId);
bool isNonEmptyTitle(const std::string& title);

#endif
