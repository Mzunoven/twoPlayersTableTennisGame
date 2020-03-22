#include "player.h"

Player::Player() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  makeRacket2d();
  makeFace2d();
  makeHandle2d();
  makeFace3d(-0.1f, 0.7f);
  makeHandle3d(0.0f, 0.6f);
  makeRacket3d(0.0f, 0.6f);
}

Player::Player(float nx, float ny, float nz) {
  x = nx;
  y = ny;
  z = nz;
  makeRacket2d();
  makeFace2d();
  makeHandle2d();
  makeFace3d(-0.1f, 0.7f);
  makeHandle3d(0.0f, 0.6f);
  makeRacket3d(0.0f, 0.6f);
}

void Player::makeHandle2d() {
  handle2d = vector<float> {
    0.0f, -15.7f, -1.65f,
    0.0f, -10.6f, -1.5f,
    0.0f, -7.5f, -1.4f,
    0.0f, -7.5f, 1.4f,
    0.0f, -10.6f, 1.5f,
    0.0f, -15.7f, 1.65f,
    0.0f, -15.7f, -1.65f
  };
}

void Player::makeRacket2d() {
  racket2d = vector<float> {
    0.0f, -15.7f, -1.65f,
    0.0f, -10.6f, -1.5f,
    0.0f, -8.6f, -2.5f,
    0.0f, -7.5f, -4.0f,
    0.0f, -6.5f, -5.45f,
    0.0f, -5.0f, -6.65f,
    0.0f, -2.5f, -7.45f,
    0.0f, 0.0f, -7.55f,
    0.0f, 3.0f, -7.3f,
    0.0f, 4.5f, -6.82f,
    0.0f, 6.0f, -6.05f,
    0.0f, 7.5f, -4.5f,
    0.0f, 8.25f, -3.5f,
    0.0f, 9.0f, 0.0f,
    0.0f, 8.25f, 3.5f,
    0.0f, 7.5f, 4.5f,
    0.0f, 6.0f, 6.05f,
    0.0f, 4.5f, 6.82f,
    0.0f, 3.0f, 7.3f,
    0.0f, 0.0f, 7.55f,
    0.0f, -2.5f, 7.45f,
    0.0f, -5.0f, 6.65f,
    0.0f, -6.5f, 5.45f,
    0.0f, -7.5f, 4.0f,
    0.0f, -8.6f, 2.5f,
    0.0f, -10.6f, 1.5f,
    0.0f, -15.7f, 1.65f,
    0.0f, -15.7f, -1.65f
  };

  filler2d = vector<float> {
    0.0f, -7.5f, -4.0f,
    0.0f, -10.6f, -1.5f,
    0.0f, -10.6f, 1.5f,
    0.0f, -7.5f, 4.0f,
    0.0f, -7.5f, -4.0f,
  };
}

void Player::makeFace2d() {
  face2d = vector<float> {
    0.0f, -7.5f, -4.0f,
    0.0f, -6.5f, -5.45f,
    0.0f, -5.0f, -6.65f,
    0.0f, -2.5f, -7.45f,
    0.0f, 0.0f, -7.55f,
    0.0f, 3.0f, -7.3f,
    0.0f, 4.5f, -6.82f,
    0.0f, 6.0f, -6.05f,
    0.0f, 7.5f, -4.5f,
    0.0f, 8.25f, -3.5f,
    0.0f, 9.0f, 0.0f,
    0.0f, 8.25f, 3.5f,
    0.0f, 7.5f, 4.5f,
    0.0f, 6.0f, 6.05f,
    0.0f, 4.5f, 6.82f,
    0.0f, 3.0f, 7.3f,
    0.0f, 0.0f, 7.55f,
    0.0f, -2.5f, 7.45f,
    0.0f, -5.0f, 6.65f,
    0.0f, -6.5f, 5.45f,
    0.0f, -7.5f, 4.0f,
    0.0f, -7.5f, -4.0f
  };
}

void Player::makeRacket3d(float xFront, float xBack) {
  auto nom = crossProduct({racket2d[0] - racket2d[3], racket2d[1] - racket2d[4], racket2d[2] - racket2d[5]}, {racket2d[6] - racket2d[3], racket2d[7] - racket2d[4], racket2d[8] - racket2d[5]});
  for (int i = 0; i < filler2d.size(); i++) {
    if (i%3 == 0) {
      racketFrontVtx.push_back(filler2d[i] + xFront);
      racketBackVtx.push_back(filler2d[i] + xBack);
    }
    else {
      racketFrontVtx.push_back(filler2d[i]);
      racketBackVtx.push_back(filler2d[i]);
    }
    racketFrontNom.push_back(nom[0]);
    racketFrontNom.push_back(nom[1]);
    racketFrontNom.push_back(nom[2]);
  }
  connectSurfaces(racket2d, racketSideVtx, racketSideNom, racketCol, {244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f, 0.0}, xFront, xBack);

}

void Player::makeHandle3d(float xFront, float xBack) {
  handleFrontNom = crossProduct({face2d[0] - face2d[3], face2d[1] - face2d[4], face2d[2] - face2d[5]},
                          {face2d[6] - face2d[3], face2d[7] - face2d[4], face2d[8] - face2d[5]});
  for (int i = 0; i < handle2d.size(); i++) {
    if (i%3 == 0) {
      handleFrontVtx.push_back(handle2d[i] + xFront - 0.7);
      handleBackVtx.push_back(handle2d[i] + xBack + 0.7);
    }
    else {
      handleFrontVtx.push_back(handle2d[i]);
      handleBackVtx.push_back(handle2d[i]);
    }
  }

  connectSurfaces(handle2d, handleSideVtx, handleSideNom, handleCol, {139.0f/255.0f, 69.0f/255.0f, 19.0f/255.0f, 0.0}, -0.7, 0.0);
  connectSurfaces(handle2d, handleSideVtx, handleSideNom, handleCol, {139.0f/255.0f, 69.0f/255.0f, 19.0f/255.0f, 0.0}, 0.6, 1.3);
}

void Player::connectSurfaces(vector<float>& vec2d, vector<float>& vtx, vector<float>& nom, vector<float>& col, vector<float> targetCol, float xFront, float xBack) {
  for (int i = 0; i < vec2d.size() - 3; i += 3) {
    vtx.push_back(vec2d[i] + xFront);
    vtx.push_back(vec2d[i + 1]);
    vtx.push_back(vec2d[i + 2]);
    vtx.push_back(vec2d[i + 3] + xFront);
    vtx.push_back(vec2d[i + 4]);
    vtx.push_back(vec2d[i + 5]);
    vtx.push_back(vec2d[i + 3] + xBack);
    vtx.push_back(vec2d[i + 4]);
    vtx.push_back(vec2d[i + 5]);
    vtx.push_back(vec2d[i] + xBack);
    vtx.push_back(vec2d[i + 1]);
    vtx.push_back(vec2d[i + 2]);

    auto n = crossProduct({vec2d[i] - vec2d[i + 3], vec2d[i + 1] - vec2d[i + 4],
                             vec2d[i + 2] - vec2d[i + 5]}, {xBack - xFront, 0.0f, 0.0f});

    for (int j = 0; j < 4; j++) {
       nom.push_back(n[0]);
       nom.push_back(n[1]);
       nom.push_back(n[2]);

       col.push_back(targetCol[0]);
       col.push_back(targetCol[1]);
       col.push_back(targetCol[2]);
       col.push_back(targetCol[3]);
    }
  }
}

void Player::makeFace3d(float xfront, float xback) {
  faceFrontNom = crossProduct({face2d[0] - face2d[3], face2d[1] - face2d[4], face2d[2] - face2d[5]},
                          {face2d[6] - face2d[3], face2d[7] - face2d[4], face2d[8] - face2d[5]});
  faceBackNom = faceFrontNom;
  for (int i = 0; i < face2d.size(); i++) {
    if (i%3 == 0) {
      faceFrontVtx.push_back(face2d[i] + xfront);
      faceBackVtx.push_back(face2d[i] + xback);
    }
    else {
      faceFrontVtx.push_back(face2d[i]);
      faceBackVtx.push_back(face2d[i]);
    }
  }
  faceFrontCol = {1.0f, 0.0f, 0.0f, 0.5f};
  faceBackCol = {0.0f, 0.0f, 0.0f, 0.5f};
}

vector<float> Player::crossProduct(vector<float> vec1, vector<float> vec2) {
  vector<float> norm = {vec1[1]*vec2[2] - vec1[2]*vec2[1],
                        vec1[2]*vec2[0] - vec1[0]*vec2[2],
                        vec1[0]*vec2[1] - vec1[1]*vec2[0]};

  float mag = sqrt(pow(norm[0], 2.0f) + pow(norm[1], 2.0f) + pow(norm[2], 2.0f));

  norm[0] /= mag;
  norm[1] /= mag;
  norm[2] /= mag;
  return norm;
}

void Player::drawPolygon(vector<float>& vtx, vector<float>& nom, vector<float>& col) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, col.data());
  glNormalPointer(GL_FLOAT, 0, nom.data());
  glVertexPointer(3, GL_FLOAT, 0, vtx.data());
  glDrawArrays(GL_POLYGON, 0, vtx.size()/3);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void Player::drawQuads(vector<float>& vtx, vector<float>& nom, vector<float>& col) {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_FLOAT, 0, col.data());
  glNormalPointer(GL_FLOAT, 0, nom.data());
  glVertexPointer(3, GL_FLOAT, 0, vtx.data());
  glDrawArrays(GL_QUADS, 0, vtx.size()/3);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

void Player::draw() {
  // draw surface
  drawPolygon(faceFrontVtx, faceFrontNom, faceFrontCol);
  drawPolygon(faceBackVtx, faceBackNom, faceBackCol);
  drawPolygon(handleFrontVtx, handleFrontNom, handleCol);
  drawPolygon(handleBackVtx, handleFrontNom, handleCol);
  drawQuads(racketFrontVtx, racketFrontNom, racketCol);
  drawQuads(racketBackVtx, racketFrontNom, racketCol);
  drawQuads(handleSideVtx, handleSideNom, handleCol);
  drawQuads(racketSideVtx, racketSideNom, racketCol);
}


void Player::updateNormal() {

}

void Player::updatePosition(float nx, float ny) {
  x = nx;
  y = ny;
}
