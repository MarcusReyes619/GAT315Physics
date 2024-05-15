#include "raylib.h"

typedef struct ncContact ncContact_t;
typedef struct NcBody NcBody;

void CreateContacts(NcBody* bodies, ncContact_t** contacts);
ncContact_t* GenerateContact(NcBody* body1, NcBody* body2);

void SeparateContacts(ncContact_t* contacts);
void ResolveContacts(ncContact_t* contacts);