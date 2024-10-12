#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(200);
	ofSetCircleResolution(60);
	ofNoFill();
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto param = ofGetFrameNum() % 50;
	if (param < 20) { this->noise_step += 0; }
	else if (param < 25) { this->noise_step += ofMap(param, 20, 25, 0, 0.025); }
	else if (param < 45) { this->noise_step += 0.025; }
	else { this->noise_step += ofMap(param, 45, 50, 0.025, 0); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -600; x <= 600; x += 600) {

		for (int y = -600; y <= 600; y += 600) {

			ofPushMatrix();
			ofTranslate(x, y);
			ofRotateY(ofGetFrameNum() * 1.44);

			auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			for (int i = 0; i < 30; i++) {

				ofSetLineWidth(ofMap(i, 0, 30, 0, 2));

				ofPushMatrix();
				ofRotateZ(ofMap(ofNoise(noise_seed.z, this->noise_step + i * 0.005), 0, 1, -360, 360));
				ofRotateY(ofMap(ofNoise(noise_seed.y, this->noise_step + i * 0.005), 0, 1, -360, 360));
				ofRotateX(ofMap(ofNoise(noise_seed.x, this->noise_step + i * 0.005), 0, 1, -360, 360));

				ofDrawCircle(glm::vec3(), 250);

				ofPopMatrix();
			}

			ofPopMatrix();
		}
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}