
typedef struct ncSpring {

	struct NcBody* body1;
	struct NcBody* body2;
	float restLength;
	float k; //stiffness

	struct ncSpring* next;
	struct ncSpring* prev;
}ncSpring_t;

extern ncSpring_t* ncSprings;
extern int ncSpringCount;

ncSpring_t* CreateSpring(struct NcBody* body1,struct NcBody* body2, float restLength, float k);
void AddSpring(ncSpring_t* spring);
void DestorySpring(ncSpring_t* spring);
void DestoryAllSprings();

void ApplySpringForce(ncSpring_t* spring);

