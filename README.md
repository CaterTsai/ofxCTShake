ofxCTShake
====================

Description
-----------
An openframeworks add-on to easy create the hand-drawn style

Just drawing between begin() and end():

	ofxCTShakeCanvas	_ShakeCanvas;
	void ofApp::draw()
	{
		_ShakeCanvas.begin();
		{
			ofSetColor(255);
			ofCircle(100, 100, 50);
		}
		_ShakeCanvas.end();
		
		//Draw the hand-drawn style
		_ShakeCanvas.draw();
	}

You can setting your own shake method using ofxCTShakeCanvas::setFunc().

Example
-------
The example is test on visual studio 2012 with openframework 0.8.1.

![ofxCTShake example](https://dl.dropboxusercontent.com/u/23887512/GitHub/ofxShake.gif)

see [Video](https://youtu.be/djlZcAZB4qY)
