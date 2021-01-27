#include "read_json.h"

Dane *interpret_response(const char *const chunk, Dane *dane)
{
    // printf("json::: %s",chunk);
    const cJSON *payload = NULL;
    // const cJSON *status = NULL;

    // printf("zainicjowalem payload\n");
    cJSON *game_json = cJSON_Parse(chunk);
    // printf("parse\n");
    if (game_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
    else
    {
        payload = cJSON_GetObjectItemCaseSensitive(game_json, "payload");
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *list = cJSON_GetObjectItemCaseSensitive(payload, "list");
        if (list != NULL)
        {

            cJSON *object = NULL;
            int i = 0;
            // printf("inicjuje obiekt\n");
            cJSON_ArrayForEach(object, list)
            {
                cJSON *x = cJSON_GetObjectItemCaseSensitive(object, "x");
                cJSON *y = cJSON_GetObjectItemCaseSensitive(object, "y");
                cJSON *type = cJSON_GetObjectItemCaseSensitive(object, "type");
                dane->x[i] = x->valueint;
                dane->y[i] = y->valueint;
                dane->field[i] = (char *)malloc(sizeof(char) * strlen((type->valuestring) + 1));
                strcpy(dane->field[i], type->valuestring);
                dane->mess = 3;
                i++;
            }
        }
        else if (current_x != NULL)
        {
            cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
            cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
            cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
            dane->x[0] = current_x->valueint;
            dane->y[0] = current_y->valueint;
            dane->field[0] = field_type->valuestring;
            dane->direction = direction->valuestring;
            dane->mess = 1;
        }
    }
    return dane;
}
