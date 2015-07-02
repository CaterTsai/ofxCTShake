#pragma once

#include "ofMain.h"
#include "ofxCTShake.h"

class ctGiraffe
{
public:
	void setup(float fScale = 200)
	{
		_fScale = fScale;
		
		_Outline.clear();
		_Outline.setFilled(false);
		_Outline.setStrokeWidth(3.0);
		_Outline.setStrokeColor(ofColor(255));

		_DrawStartPos.set(-0.15 * fScale, -(fScale * 0.95));
		ofPoint StartPos_ = _DrawStartPos;

		_Outline.moveTo(StartPos_);
				
		//Mouse
		_Outline.bezierTo(	StartPos_.x - (0.4 * fScale), StartPos_.y, 
							StartPos_.x - (0.4 * fScale), StartPos_.y - (0.1 * fScale),
							StartPos_.x, StartPos_.y - (0.2 * fScale));


		//Tongue
		_TongueStart = ofBezierPoint(	StartPos_,
										ofPoint(StartPos_.x - (0.4 * fScale), StartPos_.y),
										ofPoint(StartPos_.x - (0.4 * fScale), StartPos_.y - (0.1 * fScale)),
										ofPoint(StartPos_.x, StartPos_.y - (0.2 * fScale)),
										0.2
										);

		_TongueEnd = ofBezierPoint(	StartPos_,
									ofPoint(StartPos_.x - (0.4 * fScale), StartPos_.y),
									ofPoint(StartPos_.x - (0.4 * fScale), StartPos_.y - (0.1 * fScale)),
									ofPoint(StartPos_.x, StartPos_.y - (0.2 * fScale)),
									0.3
									);
		

		//Horn
		StartPos_.set(StartPos_.x, StartPos_.y - (0.2 * fScale));
		_Outline.bezierTo( StartPos_.x + (0.05 * fScale), StartPos_.y - (0.15 * fScale),
						StartPos_.x + (0.125 * fScale), StartPos_.y - (0.175 * fScale),
						StartPos_.x + (0.125 * fScale), StartPos_.y);

		//Ear
		StartPos_.set(StartPos_.x + (0.125 * fScale), StartPos_.y);
		_Outline.bezierTo( StartPos_.x + (0.15 * fScale), StartPos_.y,
						StartPos_.x + (0.15 * fScale), StartPos_.y + (0.15 * fScale),
						StartPos_.x, StartPos_.y + (0.15 * fScale));

		//Neck
		_Outline.lineTo( StartPos_.x + (0.175 * fScale), StartPos_.y + fScale);
		_Outline.lineTo( StartPos_.x - (0.125 * fScale), StartPos_.y + fScale);
		_Outline.close();

		//Spot
		ofVec2f LinePos_;
		LinePos_.set(StartPos_.x, StartPos_.y + (0.15 * fScale));
		_SpotsStart1 = LinePos_.getInterpolated(ofVec2f(StartPos_.x + (0.175 * fScale), StartPos_.y + fScale), 0.2);
		_SpotsEnd1 = LinePos_.getInterpolated(ofVec2f(StartPos_.x + (0.175 * fScale), StartPos_.y + fScale), 0.5);
		
		LinePos_ = _DrawStartPos;
		_SpotsStart2 = LinePos_.getInterpolated(ofVec2f(StartPos_.x - (0.125 * fScale), StartPos_.y + fScale), 0.6);
		_SpotsEnd2 = LinePos_.getInterpolated(ofVec2f(StartPos_.x - (0.125 * fScale), StartPos_.y + fScale), 0.9);
	}
	void draw()
	{
		ofSetColor(255);

		_Outline.draw();

		//Tongue
		ofBezier(	_TongueStart.x, _TongueStart.y,
					_TongueStart.x - (0.075 * _fScale), _TongueStart.y + (0.05 * _fScale),
					_TongueEnd.x - (0.075 * _fScale), _TongueEnd.y + (0.05 * _fScale),
					_TongueEnd.x, _TongueEnd.y
					);

		//Eyes
		ofCircle(_DrawStartPos.x, _DrawStartPos.y - (0.1 * _fScale), (0.025 * _fScale));

		//Spots
		ofBezier(	_SpotsStart1.x, _SpotsStart1.y,
					_SpotsStart1.x - (0.1 * _fScale), _SpotsStart1.y,
					_SpotsEnd1.x - (0.1 * _fScale), _SpotsEnd1.y,
					_SpotsEnd1.x, _SpotsEnd1.y
					);

		ofBezier(	_SpotsStart2.x, _SpotsStart2.y,
					_SpotsStart2.x + (0.1 * _fScale), _SpotsStart2.y,
					_SpotsEnd2.x + (0.1 * _fScale), _SpotsEnd2.y,
					_SpotsEnd2.x, _SpotsEnd2.y
					);
	}
private:
	ofPath		_Outline;
	ofPoint		_TongueStart, _TongueEnd;
	float		_fScale;
	ofPoint		_DrawStartPos;
	
	ofPoint		_SpotsStart1, _SpotsEnd1;
	ofPoint		_SpotsStart2, _SpotsEnd2;

};

class ctStar
{
public:
	void setup(float fOutRadius, float fInRaduis)
	{
		//Create a star
		float fOutDegree_ = 0.0;
		float fInDegree_ = 36.0;
		_Star.clear();
		_Star.moveTo(0, -fOutRadius);
		for (int idx_ = 0; idx_ < 5; idx_++, fOutDegree_ += 72, fInDegree_ += 72)
		{
			_Star.lineTo(sin(fOutDegree_ * DEG_TO_RAD) * fOutRadius, -cos(fOutDegree_ * DEG_TO_RAD) * fOutRadius);
			_Star.lineTo(sin(fInDegree_ * DEG_TO_RAD) * fInRaduis, -cos(fInDegree_ * DEG_TO_RAD) * fInRaduis);
		}
		_Star.lineTo(0, -fOutRadius);
		_Star.close();
	}

	void draw(float fScale)
	{
		ofSetColor(255);
		ofPath _CopyStar = _Star;
		_CopyStar.scale(fScale, fScale);
		_CopyStar.draw();
	}
private:
	ofPath	_Star;
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

private:
	ofxCTShakeCanvas	_ShakeCanvas;
	ctGiraffe			_Giraffe;
	ctStar				_Star;
};
