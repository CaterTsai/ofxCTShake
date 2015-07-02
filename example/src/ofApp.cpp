#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofBackground(85, 143, 216);
	
	ofSetVerticalSync(true);

	_Giraffe.setup();
	_Star.setup(25, 15);
	_ShakeCanvas.setup();
	_ShakeCanvas.startShake();
}

//--------------------------------------------------------------
void ofApp::update()
{
	if( ofGetFrameNum() % 5 == 0)
	{
		_ShakeCanvas.update();		
	}

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(18, 45, 78), ofColor(85, 143, 216), OF_GRADIENT_LINEAR);
	//draw on shake canvae
	ofPushStyle();
	_ShakeCanvas.begin();
	{
		//Giraffe
		ofPushMatrix();
		ofTranslate(_ShakeCanvas.getWidth() - 100, _ShakeCanvas.getHeight());
		{
			_Giraffe.draw();
		}
		ofPopMatrix();

		//Star
		ofPushMatrix();
		ofTranslate(500, 100);
		ofRotateZ(60);
		{			
			_Star.draw(0.6);
		}
		ofPopMatrix();
		
		ofPushMatrix();
		ofTranslate(430, 250);
		ofRotateZ(250);
		{			
			_Star.draw(0.7);
		}
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(300, 50);
		ofRotateZ(-40);
		{			
			_Star.draw(0.8);
		}
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(150, 300);
		ofRotateZ(150);
		{			
			_Star.draw(0.7);
		}
		ofPopMatrix();


		//Ground
		ofSetColor(255);
		ofSetLineWidth(3);
		ofLine(0, _ShakeCanvas.getHeight() - 25, _ShakeCanvas.getWidth(), _ShakeCanvas.getHeight() - 25);
		
		//Moon
		ofCircle(100, 100, 50);

	}
	_ShakeCanvas.end();
	ofPopStyle();

	//draw shake canvae
	_ShakeCanvas.draw();
}