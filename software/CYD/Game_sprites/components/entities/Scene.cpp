/*! \brief Scene create implementation
*
*/
#include "Scene.hpp"

Scene::Scene()
: count_(0),
  inputTarget_(0)
{
    for (int i = 0; i < kMaxEntities; ++i) {
        entities_[i] = 0;
    }
}

bool Scene::add(Entity* e) {
    if (count_ >= kMaxEntities) return false;
    entities_[count_] = e;
    ++count_;
    return true;
}

void Scene::update(float dt, int screenW, int screenH) {
    for (int i = 0; i < count_; ++i) {
        entities_[i]->update(dt, screenW, screenH);
    }
}

void Scene::draw(Ili9341Display& d) const {
    for (int i = 0; i < count_; ++i) {
        entities_[i]->draw(d);
    }
}

void Scene::setInputTarget(InputListener* t) {
    inputTarget_ = t;
}

void Scene::onButton(Button b) {
    if (inputTarget_) {
        inputTarget_->onButton(b);
    }
}
