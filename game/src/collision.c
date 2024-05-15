#include "collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

bool Intersects(NcBody* body1, NcBody* body2) {

	//if the distence is less then the raduis
	float distance = Vector2Distance(body1->pos, body2->pos);
	float raduis = body1->mass + body2->mass;

	return(distance <= raduis);
}

void CreateContacts(NcBody* bodies, ncContact_t** contacts) {

	for (NcBody* body = bodies; body; body = body->next) {

		for (NcBody* body2 = body->next; body2; body2 = body2->next) {
			if (body == body2)continue;
			if (body != BT_DYNIMIC && body2 != BT_DYNIMIC) continue;

			if (Intersects(body, body2)) {
				ncContact_t* contact = GenerateContact(body, body2);
				AddContact(contact, contacts);
			}

		}
	}
}
ncContact_t* GenerateContact(NcBody* body1, NcBody* body2) {
	
	ncContact_t* contact = (ncContact_t*)malloc(sizeof(ncContact_t));
	assert(contact);

	memset(contact, 0, sizeof(ncContact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->pos, body2->pos);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;

}

void SeparateContacts(ncContact_t* contacts) {


}
void ResolveContacts(ncContact_t* contacts) {


}