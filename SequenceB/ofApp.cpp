#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("The Marionette Maps");

	ofBackground(0.0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int size = 4;

	ofSetColor(sin(ofGetFrameNum()) + 1 * 64);


	for (int x = -500; x < ofGetWidth(); x += size) {

		for (int y = -500; y < ofGetHeight(); y += size) {

			float deg = 
				ofMap(
					
					ofNoise(
						(floor((x* 0.0035)*8)/8) ,
						(floor((y* 0.0035)*8)/8),
						ofGetFrameNum() * 0.03
					), 
					
					0, 1, 
					
					
					-360, 360);


			this->mesh.addVertex
			(
				glm::vec3
				(
					x + size * 3 * cos(deg * DEG_TO_RAD), 
					y + size * 3 * sin(deg * DEG_TO_RAD), 
					deg*0.2
				)
			);


			this->mesh.addColor(ofDefaultColorType(
				deg,
				deg,
				deg,
				//don't worry about alpha
				1));

			

		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	

	this->cam.begin();

	ofRotateY(sin(ofGetFrameNum()*0.02) *90.0);
	//ofRotateX(cos(ofGetFrameNum()*0.02) *90.0);
	//ofRotateZ(0.0);


	this->mesh.drawVertices();
	this->mesh.drawFaces();
	

}
