#include <cstdlib>
#include <cstring>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void UpdateHostAboutError(const char *error_message);

int ValidateValueProvided(const char *value, const char *error_message) {
  if ((value == NULL) || (value[0] == '\0')) {
    UpdateHostAboutError(error_message);
    return 0;
  }
  return 1;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
int ValidateName(char *name, int maximum_length) {
  if (ValidateValueProvided(name, "A product name must be provided.") == 0) {
    return 0;
  }
  if (strlen(name) > maximum_length) {
    UpdateHostAboutError("The product name is too long");
    return 0;
  }
  return 1;
}

int IsCategoryIdInArray(char *selected_category_id, int *valid_category_ids,
                        int array_length) {
  int category_id = atoi(selected_category_id);
  for (int index = 0; index < array_length; index++) {
    if (valid_category_ids[index] == category_id) {
      return 1;
    }
  }
  return 0;
}

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
int ValidateCategory(char *category_id, int *valid_category_ids, int array_length) {
  if (ValidateValueProvided(category_id, "A product category mush be selected.") == 0)
    return 0;

  if ((valid_category_ids == NULL) | (array_length == 0)) {
    UpdateHostAboutError("There are no product categories available.");
    return 0;
  }

  if (IsCategoryIdInArray(category_id, valid_category_ids, array_length) == 0) {
    UpdateHostAboutError("The selected product category is not valid.");
    return 0;
  }
  return 1;
}

#ifdef __cplusplus
}
#endif
