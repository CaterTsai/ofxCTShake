#include "ofxCTShake.h"

void ofxCTShakeCanvas::setup(int iWidth, int iHeight)
{
	//allocate fbo
	_Canvas.allocate(iWidth, iHeight, GL_RGBA);
	_bAllocate = true;
	
	//initial mesh
	float fWUnit_ = (float)iWidth / (_iDensityX - 1);
	float fHUnit_ = (float)iHeight / (_iDensityY - 1);

	_Mesh.enableTextures();
	_Mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLES);
	for(int y = 0; y < _iDensityY; y++)
	{
		int yvalue = y * fHUnit_;
		for(int x = 0; x < _iDensityX; x++)
		{
			int xvalue = x * fWUnit_;
			_Mesh.addVertex(ofPoint(xvalue, yvalue, 0));
			_Mesh.addTexCoord(ofVec2f(xvalue, yvalue));
			
			_VertexSet.push_back(ofPoint(xvalue, yvalue, 0));
		}
	}

	for(int y = 0; y < _iDensityY - 1; y++)
	{
		for(int x = 0; x < _iDensityX - 1; x++)
		{
			_Mesh.addIndex(x + y * _iDensityX);
			_Mesh.addIndex((x + 1) + y * _iDensityX);
			_Mesh.addIndex(x + (y + 1) * _iDensityX);			
						
			_Mesh.addIndex((x + 1) + y * _iDensityX);
			_Mesh.addIndex(x + (y + 1) * _iDensityX);
			_Mesh.addIndex((x + 1) + (y + 1) * _iDensityX);
		}
	}

	//set
	this->setFunc(
		[]() -> int
		{
			return ofRandom(-5, 5);
		}
	);
}

//--------------------------------------------------------------
void ofxCTShakeCanvas::update()
{
	if(_bAllocate && _bShake)
	{
		this->updateMesh();
	}	
}

//--------------------------------------------------------------
void ofxCTShakeCanvas::draw()
{
	this->draw(0, 0);
}

//--------------------------------------------------------------
void ofxCTShakeCanvas::draw(int x, int y)
{
	if(_bAllocate)
	{
		ofPushMatrix();
		ofTranslate(x, y);

		ofPushStyle();
		ofSetColor(255);
		{
			_Canvas.getTextureReference().bind();
			_Mesh.draw();
			_Canvas.getTextureReference().unbind();
		}
		ofPopStyle();

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofxCTShakeCanvas::draw(ofPoint pos)
{
	this->draw(pos.x, pos.y);
}

//--------------------------------------------------------------
void ofxCTShakeCanvas::updateMesh()
{
	for(int idx_ = 0; idx_ < _Mesh.getNumVertices(); idx_++)
	{
		auto Vex_ = _Mesh.getVertex(idx_);
		Vex_.x = _VertexSet[idx_].x + _ShakeFunc();
		Vex_.y = _VertexSet[idx_].y + _ShakeFunc();
		_Mesh.setVertex(idx_, Vex_);
	}
}