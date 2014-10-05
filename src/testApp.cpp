#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	cheatmode =-1;
	setupmode =1;
	
	screenHeight = ofGetHeight();
	screenWidth = ofGetWidth();

    ofBackground(255,255,255);
	ballPos.set(screenWidth/2, screenHeight/2);
	//ballSpeed.set(2.5, -.5);
	ballSpeed.set(0, 0);

	ballSize = 50;
	
	paddleWidth = 50;
	paddleHeight = 200;
	paddleA.set(0, screenHeight/2);
	paddleB.set(screenWidth-paddleWidth, screenHeight/2);
	paddleSpeed = 5;
	
	//ofSetFrameRate(60);
	
	//info = screenWidth;

	context.setup();
	context.setupUsingXMLFile();
	depth.setup(&context);
	rgb.setup(&context);
	user.setup(&context, &depth, &rgb);
	//userB.setup(&context, &depth, &rgb);

	depth.toggleRegisterViewport(&rgb);
	context.toggleMirror();	
	
	//setting these to unreasonable values so they get changed immediately
	userAMax=5;
	userAMin= 900;
	userBMax=5;
	userBMin= 900;
	userAScore =0;
	userBScore = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	context.update();
	user.update();
	
	// find the neck...or hands.
	for (int i = 0; i < user.getTrackedUsers().size(); i++) {
		ofxTrackedUser* tracked = user.getTrackedUser(i);
		if (tracked != NULL && i==0 && tracked->neck.found) 
		{	neckA = tracked-> neck.end;

		}
		if (tracked != NULL && user.getTrackedUsers().size() >1 && i==1 && tracked->neck.found) 
		{
			neckB = tracked-> neck.end;

		}
		
	} //end tracking loops
	
	// move the ball!
	ballPos.set(ballPos.x+ballSpeed.x, ballPos.y+ ballSpeed.y);
	
	//bounce off top and bottom 
	if ((ballPos.y -ballSize<= 0)||(ballPos.y +ballSize >= screenHeight))
	{
		ballSpeed.set(ballSpeed.x, -1* ballSpeed.y);
	}
	
	//bounce off paddles
	if (ballPos.x -ballSize <= paddleA.x +paddleWidth)
		if ((ballPos.y -ballSize>= paddleA.y -paddleHeight)&&(ballPos.y -ballSize<= paddleA.y +paddleHeight))
		{
			ballSpeed.set(ballSpeed.x *-1.2, ballSpeed.y);
			info= "noo goal";
		}
	

	// bounce for paddle B
	if (ballPos.x +ballSize >= paddleB.x)
		if ((ballPos.y -ballSize>= paddleB.y -paddleHeight)&&(ballPos.y -ballSize<= paddleB.y +paddleHeight))
		{
			ballSpeed.set(ballSpeed.x *-1.2, ballSpeed.y);
			info= "...";
		}
	
	
	// Point condition:. GOAAL
	if ((ballPos.x -ballSize<= 0)||(ballPos.x +ballSize >= screenWidth))
	{
		if (ballSpeed.x > 0)
		{
			userAScore++;
			ballSpeed.set(-2.5,  ballSpeed.y);
		}
		else{
			userBScore++;
			ballSpeed.set(2.5,  ballSpeed.y);
		}
		ballPos.set(screenWidth/2, screenHeight/2);
		info = "GOOOOAAAAALLLLLL!";
	}
	
	//*************************
	// Kinect track for paddles
	
	if (setupmode==1)
	{
		info = "Setup Mode! Assume the position, & when you're 'found', move up and down as much as you plan to during the game."; 
		if (neckA !=NULL)
		{
		
			info2 = "ONE USER FOUND!";
			if (neckA.y > userAMax)
				userAMax= neckA.y;
			if (neckA.y < userAMin)
				userAMin= neckA.y;
			//cout  << "userAMax: ";
			//cout  << userAMax;
			//cout  << "userAMin: ";
			//cout  << userAMin;
			//cout << endl;
			
		}
		if ((neckA != NULL)&&(neckB !=NULL))
		{
			info2= "TWO USERS FOUND";
			
			if (neckA.y > userAMax)
				userAMax= neckA.y;
			if (neckB.y > userBMax)
				userBMax= neckB.y;
			
			if (neckA.y < userAMin)
				userAMin= neckA.y;
			if (neckB.y < userBMin)
				userBMin= neckB.y;
		}
		
		paddleA.set(paddleA.x, ofMap(neckA.y, userAMin, userAMax, 0, screenHeight));
		paddleB.set(paddleB.x, ofMap(neckB.y, userBMin, userBMax, 0, screenHeight));

	}//end setupmode
	
	else
	{
		if (neckA != NULL)
			paddleA.set(paddleA.x, ofMap(neckA.y, userAMin, userAMax, 0, screenHeight));
		
		if (neckB !=NULL)
			paddleB.set(paddleB.x, ofMap(neckB.y, userBMin, userBMax, 0, screenHeight));

	}
	
	
	
 
}

//--------------------------------------------------------------
void testApp::draw(){


	
	//draw the ball
	ofSetColor(100, 100, 100);
	ofCircle(ballPos.x, ballPos.y, ballSize);
	
	//draw the paddles
	ofSetColor(150, 150, 150);
	ofRect(paddleA.x, paddleA.y, paddleWidth, paddleHeight);
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(ofToString(userAScore) , paddleA.x+paddleWidth/2.5, paddleA.y+paddleHeight/2.5); 
	
	ofSetColor(150, 150, 150);
	ofRect(paddleB.x, paddleB.y, paddleWidth, paddleHeight);
	ofSetColor(0, 0, 255);
	ofDrawBitmapString(ofToString(userBScore) , paddleB.x+paddleWidth/2.5, paddleB.y+ paddleHeight/2.5); 

	ofSetColor(0, 0, 150);

	ofDrawBitmapString(info , 30, 30);
	ofDrawBitmapString(info2 , 30, 50);

//	user.draw();
//	ofSetColor(255, 255, 255);
//
//	liveImg.setFromPixels(rgb.getImagePixels(), 640, 480, OF_IMAGE_COLOR);
//	
//	//liveImg.draw(0,0);
//	
//	//just trying to get neckA
//	int headsize = 50;
//	
//	int headNWx = neckA.x -headsize;
//	int headNWy= neckA.y -headsize;
//	
//	vector <unsigned char > x;
//	for (int i=headNWy; i<headNWy+headsize; i++) //this is y
//		{
//			for (int j=headNWx; j<headNWx+headsize; j++)   //this is x
//			{
//				x.push_back(liveImg.getPixels()[i*j+j]);
//				//cout << x;
//				//cout << endl;
//			}
//		}
//	
//	liveImg.setFromPixels(x, headsize*2, headsize*2, OF_IMAGE_COLOR);
//	liveImg.draw(0,0);
	
	if (cheatmode==1)
	{
		ofSetLineWidth(1);
		ofSetColor(255, 255, 255);
		
		depth.draw(640,0,640,480);
		rgb.draw(0, 0, 640, 480);
		user.draw();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		user.drawUserMasks(0, 0);
		glDisable(GL_BLEND);
		
//		ofSetColor(255, 0, 0);
//		ofCircle(leftHand.x, leftHand.y, 10);
//		ofCircle(rightHand.x, rightHand.y, 10);				
//		ofSetLineWidth(200);
//		ofLine(leftHand.x, leftHand.y, rightHand.x, rightHand.y);
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	info = ofToString(key);
	if (key==357)
		paddleB.set(paddleB.x, paddleB.y-paddleSpeed);
	if (key==359)
		paddleB.set(paddleB.x, paddleB.y+paddleSpeed);
	
	if (key==97)
		paddleA.set(paddleA.x, paddleA.y-paddleSpeed);
	if (key==122)
		paddleA.set(paddleA.x, paddleA.y+paddleSpeed);
	
	if (key==99)
		cheatmode=cheatmode*-1;
	
	if (key==115)
	{
		if (setupmode ==1)
		{
			//starting game
			ballSpeed.set(2.5, -.5);
			
		}
		setupmode=setupmode*-1;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

void testApp::windowResized(int w, int h){

}
