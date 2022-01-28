#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1);
	ofEnableDepthTest();

	
	

	auto Box = ofBoxPrimitive();

	


	Box.set(200, 200, 200,12,12,12);

	
	

	this->Triangles.insert(this->Triangles.end(), Box.getMesh().getUniqueFaces().begin(), Box.getMesh().getUniqueFaces().end());



	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();

	int radius = 300;

	for (int i = 0; i < this->Triangles.size(); i++) {

		glm::vec3 avg = (this->Triangles[i].getVertex(0) + this->Triangles[i].getVertex(1) + this->Triangles[i].getVertex(2)) / 3;
		
		
		auto noise_value = ofNoise(avg.y * 0.005 + ofGetFrameNum() * 0.02, avg.x * 0.0025, avg.z * 0.0025);

		if (noise_value < 0.45) { 
			noise_value = 0.5; 
		}
		
		else if (noise_value > 0.55) { 
			noise_value = 1; 
		}
		else { 
			noise_value = ofMap(noise_value, 0.45, 0.55, 0, 1); 
		
		}

		vector<glm::vec3> vertices;


	

		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(0)) * (noise_value * 25) );
		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(1)));
		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(2)) );

		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(0)));
		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(1)));
		vertices.push_back(glm::normalize(this->Triangles[i].getVertex(2)));



		for (auto& vertex : vertices) {

			vertex *= noise_value;
			vertex += avg;
		}

		this->mesh.addVertices(vertices);
		this->frame.addVertices(vertices);

		this->mesh.addColor(ofColor(255 + noise_value));
		this->mesh.addColor(ofColor(255 + noise_value));
		this->mesh.addColor(ofColor(255 + noise_value));

		this->mesh.addColor(ofColor(255));
		this->mesh.addColor(ofColor(255));
		this->mesh.addColor(ofColor(255));

		this->frame.addColor(ofColor(255));
		this->frame.addColor(ofColor(255));
		this->frame.addColor(ofColor(255));

		this->frame.addColor(ofColor(255 + noise_value));
		this->frame.addColor(ofColor(255 + noise_value));
		this->frame.addColor(ofColor(255 + noise_value));



	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(sin(ofGetFrameNum()*0.02) *90.0);
	ofRotateX(cos(ofGetFrameNum()*0.02) *90.0);
	ofRotateZ(ofGetFrameNum());

	ofSetColor(239);
	this->frame.drawWireframe();
	

	ofSetColor(0.0);
	this->mesh.drawFaces();
	//this->frame.drawWireframe();

	this->cam.end();
}

