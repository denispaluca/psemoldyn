/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <iostream>
#include "utils/ArrayUtils.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

//static logger variable particleLogger
log4cxx::LoggerPtr particleLogger(log4cxx::Logger::getLogger("particle"));

Particle::Particle(const Particle &other) {
  x = other.x;
  v = other.v;
  f = other.f;
  old_f = other.old_f;
  m = other.m;
  type = other.type;
  delta_t = other.delta_t;
  dt_2m = other.dt_2m;
  dtsq_2m = other.dtsq_2m;
  LOG4CXX_INFO(particleLogger, "Particle generated by copy!");
}

// Todo: maybe use initializater list instead of copy?
Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, int type_arg) {
  x = x_arg;
  v = v_arg;
  m = m_arg;
  type = type_arg;
  f = {0., 0., 0.};
  old_f = {0., 0., 0.};
  delta_t = 0;
  dt_2m = 0;
  dtsq_2m = 0;
    LOG4CXX_INFO(particleLogger, "Particle generated!");
}

Particle::~Particle() {
    LOG4CXX_INFO(particleLogger, "Particle destructed!");
}

void Particle::updateDT(double delta_t) {
    this->delta_t = delta_t;
    dt_2m = delta_t / (2*m);
    dtsq_2m = dt_2m * delta_t;
}

std::array<double, 3> &Particle::getX() { return x; }

std::array<double, 3> &Particle::getV() { return v; }

std::array<double, 3> &Particle::getF() { return f; }

std::array<double, 3> &Particle::getOldF() { return old_f; }


void Particle::addF(const std::array<double, 3> &fn) {
  f[0] += fn[0];
  f[1] += fn[1];
  f[2] += fn[2];
}

void Particle::saveOldF() {
  old_f = f;
  f = {0., 0., 0.};
}

double Particle::getM() { return m; }

int Particle::getType() { return type; }

std::string Particle::toString() {
  std::stringstream stream;
  stream << "Particle: X:" << x << " v: " << v << " f: " << f
         << " old_f: " << old_f << " type: " << type;
  return stream.str();
}

void Particle::calculateV() {
    for (int i = 0; i<3; i++) {
        v[i] = v[i] + (dt_2m * (old_f[i] + f[i]));
    }
}

void Particle::calculateX() {
    for (int i = 0; i<3; i++) {
        x[i] = x[i] + delta_t * v[i] + dtsq_2m * f[i];
    }
}

bool Particle::operator==(Particle &other) {
  return (x == other.x) and (v == other.v) and (f == other.f) and
         (type == other.type) and (m == other.m) and (old_f == other.old_f);
}

bool Particle::isOut(std::array<double, 3> domain_size) {
    return
        x[0] < 0 || x[0] > domain_size[0] ||
        x[1] < 0 || x[1] > domain_size[1] ||
        x[2] < 0 || x[2] > domain_size[2];
}

void Particle::setM(double mass) {
    this->m = mass;
}

void Particle::applyGravity(double g) {
    addF({0, m*g, 0});
}

std::ostream &operator<<(std::ostream &stream, Particle &p) {
  stream << p.toString();
  return stream;
}
