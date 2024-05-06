#include "force.h"
#include "body.h"
#include "math.h"

void ApllyGravitation(NcBody* bodies, float strenghth) {

	for (NcBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (NcBody* body2 = bodies; body2; body2 = body2->next)
		{

			if (body1 == body2) continue;
	
			Vector2 direction = Vector2Subtract(body1->pos, body2->pos);
			
			float distance = Vector2Length(direction);

	
			if (distance < 1) distance = 1;
			float force = ((body1->mass * body2->mass) / (distance * distance)) * strenghth;

			direction = Vector2Scale(Vector2Normalize(direction), force);

			ApplyForce(body1, Vector2Negate(direction), FM_FORCE);
			ApplyForce(body2, direction, FM_FORCE);
		}
	}

}