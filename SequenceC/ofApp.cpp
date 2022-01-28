#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Warp Box");

	ofBackground(0.0);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);


	ofSetLineWidth(0.3);


	auto BoxMeshBase = ofBoxPrimitive();

	BoxMeshBase.set(200, 200, 200, 12, 12, 12);

	
	this->base_mesh = BoxMeshBase.getMesh();

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	

	this->draw_mesh = this->base_mesh;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	auto time = ofGetFrameNum() * 0.01;
	for (auto& v : this->draw_mesh.getVertices()) {

		for (int i = 0; i < 3; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed.x + sin(time) * 2)), 0, 1, -45, 45) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed.y + cos(time) * 2)), 0, 1, -45, 45) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.005, noise_seed.z + sin(time)  * 2)), 0, 1, -45, 45) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;

			
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2);


	ofSetColor(198, 256);
	this->draw_mesh.drawWireframe();


	ofSetColor(17);
	this->draw_mesh.draw();


	this->cam.end();
}

