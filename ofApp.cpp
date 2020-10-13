#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	for(int i = 0; i < 2; i++){

		this->location_list.push_back(glm::vec3());
		auto direction = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		direction = glm::normalize(direction) * 2;
		this->direction_list.push_back(direction);
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		this->location_list[i] += this->direction_list[i];
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		auto len = glm::length(this->location_list[i]);
		if (len > 300) {

			this->location_list.erase(this->location_list.begin() + i);
			this->direction_list.erase(this->direction_list.begin() + i);
		}

		this->mesh.addVertex(this->location_list[i]);
		this->mesh.addColor(ofColor(39, ofMap(len, 0, 300, 255, 0)));
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 50) {

				this->mesh.addIndex(i); this->mesh.addIndex(k);
			}
		}
		
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.43);
	ofRotateY(ofGetFrameNum() * 0.65);


	this->mesh.drawVertices();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 2);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}