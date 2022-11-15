#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
#ifdef randomSeed
	ofSeedRandom(randomSeed);
#endif // randomSeed
#ifdef CLK
	auto start = std::chrono::steady_clock::now();
#endif // DEBUG
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowTitle("Dynamic-obstacles");
	ofBackground(200,200,200,200);
	myfont.loadFont("Roboto-Regular.ttf", 10);
	//map = new Enviroment();
	//car.setup();

	ofVec2f w;
	w.set(0.6 * ofGetWidth(), 0);
	wall = new maze(w, 20, 160);
	obstacles *ob = wall;
	obst.push_back(ob);

	w.set(0.2*ofGetWidth(), 0.8*ofGetHeight());
	wall = new maze(w, 20, 160);
	ob = wall;
	obst.push_back(ob);

	w.set(0.1*ofGetWidth(), 0.45*ofGetHeight());
	wall = new maze(w, 480, 40);
	ob = wall;
	obst.push_back(ob);

	w.set(0.8*ofGetWidth(), 0.4*ofGetHeight());
	wall = new maze(w, 200, 180);
	ob = wall;
	obst.push_back(ob);

	w.set(0.2 * ofGetWidth(), 0.2 * ofGetHeight());
	wall = new maze(w, 40, 40);
	ob = wall;
	obst.push_back(ob);

	w.set(0.86 * ofGetWidth(), 0.1 * ofGetHeight());
	wall = new maze(w, 40, 40);
	ob = wall;
	obst.push_back(ob);

	w.set(0.72 * ofGetWidth(), 0.9 * ofGetHeight());
	wall = new maze(w, 40, 40);
	ob = wall;
	obst.push_back(ob);


	for (unsigned int i = 0; i < numberOfstaticObst; i++)
	{
		// static obstacles
		obstacles *ob = new obstacles();
		obst.push_back(ob);
	}

	// moving obstacles' info
	ofVec2f arrLocation[numberOfmovObst] = { {90, 30} };
	ofVec2f arrVector[numberOfmovObst] = { {-1, 0} };

	for (unsigned int i = 0; i < numberOfmovObst; i++)
	{
		// moving obstacles
		OBST = new movingObst(arrLocation[i], arrVector[i]);
		obstacles *ob = OBST;
		obst.push_back(ob);
	}

	cout << "Obst size: " << obst.size() << endl;

#ifdef randomSeed
	std::cout << "RandomSeed:" << randomSeed << endl;
#endif

#ifdef CLK
	auto end = std::chrono::steady_clock::now();
	std::cout << std::endl << "Setup:" << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;
#endif // DEBUG
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!updateFlag) return;
#ifdef CLK
	auto start = std::chrono::steady_clock::now();
#endif // DEBUG

#ifdef automatic
	for (auto i : obst) {
		i->move(obst);
		//cout << "location: " << i->loc() << "Radius: " << i->rad() << endl;
		//cout << i.getX() << "  " << i.getY() << endl;
	}
#endif // automatic

	if (map!= NULL) map->update(car,obst);
#ifdef CLK
	auto end = std::chrono::steady_clock::now();
	/*std::cout << std::endl << "Update:" << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;*/
	updateTime = std::chrono::duration<double, std::milli>(end - start).count();
#endif // DEBUG
}

//--------------------------------------------------------------
void ofApp::draw(){
#ifdef CLK
	auto start = std::chrono::steady_clock::now();
#endif // DEBUG

	for (auto i : obst) {
		i->render();
	}
	if (map != NULL) map->render();
	if (car!= NULL) car->render();

	char fpsStr[255]; // an array of chars
	ofSetColor({ 255,0,0 });
	sprintf(fpsStr, "Frame rate: %d", int(ofGetFrameRate()));
	myfont.drawString(fpsStr, ofGetWindowWidth() - 100, ofGetWindowHeight() - 25);
	if (map != NULL) {
		char numNode[255];
		sprintf(numNode, "Number of nodes: %d", int(map->numofnode()));
		myfont.drawString(numNode, ofGetWindowWidth() - 140, ofGetWindowHeight() - 10);
	}

#ifdef CLK
	auto end = std::chrono::steady_clock::now();
	/*std::cout << std::endl << "Draw:" << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;*/
	drawTime = std::chrono::duration<double, std::milli>(end - start).count();

	char time[255];
	sprintf(time, "Update rate: %f", updateTime);
	myfont.drawString(time, ofGetWindowWidth() - 140, ofGetWindowHeight() - 755);
	sprintf(time, "Draw rate: %f", drawTime);
	myfont.drawString(time, ofGetWindowWidth() - 140, ofGetWindowHeight() - 740);

#endif // DEBUG
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'p')
	{
		updateFlag = !updateFlag;
	}
	else if(key=='g')
	{
		map->grid = !map->grid;
	}
	else if (key == 'x') {
		ofImage img;
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		img.save("screenshot.png");
	}
#ifdef manual
	OBST->move(key);
#endif // manual

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	ofVec2f loc;
	loc.set(x, y);
	if (button == 0) {
		if (car != NULL) {
			map->targetSet(loc);
		}
	}
	else if (button == 2) {
		car = new Robot(loc);
		map = new Enviroment(car->getLocation());
	}
	else
	{

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
