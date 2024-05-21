#include "collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Function to check if two bodies intersect
bool Intersects(NcBody* body1, NcBody* body2) {
    // Calculate the distance between the two bodies
    float distance = Vector2Distance(body1->pos, body2->pos);
    // Calculate the combined radius (assuming mass is used as radius)
    float raduis = body1->mass + body2->mass;

    // Return true if the distance is less than or equal to the combined radius
    return (distance <= raduis);
}

// Function to create contacts between intersecting bodies
void CreateContacts(NcBody* bodies, ncContact_t** contacts) {
    // Iterate through each body in the list
    for (NcBody* body = bodies; body; body = body->next) {
        // Iterate through the remaining bodies in the list
        for (NcBody* body2 = body->next; body2; body2 = body2->next) {
            // Skip if the same body or both are not dynamic
            if (body == body2) continue;
            if (body->type != BT_DYNIMIC && body2->type != BT_DYNIMIC) continue;

            // If the bodies intersect, generate and add a contact
            if (Intersects(body, body2)) {
                ncContact_t* contact = GenerateContact(body, body2);
                AddContact(contact, contacts);
            }
        }
    }
}

// Function to generate a contact between two bodies
ncContact_t* GenerateContact(NcBody* body1, NcBody* body2) {
    // Allocate memory for a new contact
    ncContact_t* contact = (ncContact_t*)malloc(sizeof(ncContact_t));
    assert(contact);

    // Initialize the contact structure to zero
    memset(contact, 0, sizeof(ncContact_t));

    // Set the bodies involved in the contact
    contact->body1 = body1;
    contact->body2 = body2;

    // Calculate the direction vector and distance between the bodies
    Vector2 direction = Vector2Subtract(body1->pos, body2->pos);
    float distance = Vector2Length(direction);

    // If the distance is zero, generate a small random direction
    if (distance == 0) {
        direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
    }

    // Calculate the penetration depth
    float radius = (body1->mass + body2->mass);

    contact->depth = radius - distance;

    // Normalize the direction vector to get the contact normal
    contact->normal = Vector2Normalize(direction);

    // Calculate the average restitution for the contact
    contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

    return contact;
}

// Function to separate bodies involved in contacts
void SeparateContacts(ncContact_t* contacts) {
    // Iterate through each contact
    for (ncContact_t* contact = contacts; contact; contact = contact->next) {
        // Calculate the total inverse mass
        float totalInversMass = contact->body1->inversMass + contact->body2->inversMass;

        // Calculate the separation vector
        Vector2 separate = Vector2Scale(contact->normal, contact->depth / totalInversMass);

        // Adjust the positions of the bodies based on their inverse masses
        contact->body1->pos = Vector2Add(contact->body1->pos, Vector2Scale(separate, contact->body1->inversMass));
        contact->body2->pos = Vector2Add(contact->body2->pos, Vector2Scale(separate, -contact->body2->inversMass));
    }
}

// Function to resolve contacts by applying impulses
void ResolveContacts(ncContact_t* contacts) {
    // Iterate through each contact
    for (ncContact_t* contact = contacts; contact; contact = contact->next) {
        // Calculate the relative velocity between the bodies
        Vector2 rv = Vector2Subtract(contact->body1->vel, contact->body2->vel);

        // Calculate the normal velocity
        float nv = Vector2DotProduct(rv, contact->normal);

        // Skip if the bodies are moving apart
        if (nv > 0) continue;

        // Calculate the total inverse mass
        float tim = contact->body1->inversMass + contact->body2->inversMass;

        // Calculate the impulse magnitude
        float impulseMag = (float)(-(1 + contact->restitution) * nv / tim);

        // Calculate the impulse vector
        Vector2 impulseVec = Vector2Scale(contact->normal, impulseMag);

        // Apply the impulse to the bodies
        ApplyForce(contact->body1, impulseVec, contact->body1->type);
        ApplyForce(contact->body2, Vector2Negate(impulseVec), contact->body2->type);
    }
}
