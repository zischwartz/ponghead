#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

#include "ofxVectorMath.h"
#include "ofxOpenNI.h"

#define MAX_N_PTS         1500

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		float		speedOfRotation; // speed;

	int screenWidth;
	int screenHeight;
	
		ofxVec2f	ballPos;
		ofxVec2f	ballSpeed;
	int ballSize;
	
	ofxVec2f	paddleA;
	ofxVec2f	paddleB;
	
	int paddleWidth;
	int paddleHeight;	
	int paddleSpeed;
	
	string info;
	string info2;
	
	ofPoint leftHand;
	ofPoint rightHand;

	ofPoint neckA;
	ofPoint neckB;

	
	ofxOpenNIContext	context;
	ofxDepthGenerator	depth;
	ofxImageGenerator	rgb;
	ofxUserGenerator	user;
	//ofxUserGenerator	userB;
	
	int cheatmode;
	int setupmode;
	
	int userAMax;
	int userAMin;
	int userBMax;
	int userBMin;
	
	int userAScore;
	int userBScore;
	
};

#endif

