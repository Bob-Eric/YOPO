
// pybind11
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// flightlib
#include "flightlib/envs/vec_env.hpp"

namespace py = pybind11;
using namespace flightlib;

// vec_env -> quadrotor_env
PYBIND11_MODULE(flightgym, m) {
	py::class_<VecEnv>(m, "QuadrotorEnv_v1")
	    .def(py::init<>())
	    .def(py::init<const std::string&>())
	    .def(py::init<const std::string&, const bool>())
	    // unity
	    .def("close", &VecEnv::close)
	    .def("connectUnity", &VecEnv::connectUnity)
	    .def("disconnectUnity", &VecEnv::disconnectUnity)
	    .def("render", &VecEnv::render)
	    .def("spawnTrees", &VecEnv::spawnTrees)
	    .def("savePointcloud", &VecEnv::savePointcloud)
	    .def("spawnTreesAndSavePointcloud", &VecEnv::spawnTreesAndSavePointcloud)
	    // set
	    .def("step", &VecEnv::step)
	    .def("reset", &VecEnv::reset)
	    .def("setState", &VecEnv::setState)
	    .def("setGoal", &VecEnv::setGoal)
	    .def("setSeed", &VecEnv::setSeed)
	    .def("setMapID", &VecEnv::setMapID)
	    // get
	    .def("getNumOfEnvs", &VecEnv::getNumOfEnvs)
	    .def("getWorldBox", &VecEnv::getWorldBox)
	    .def("getObsDim", &VecEnv::getObsDim)
	    .def("getActDim", &VecEnv::getActDim)
	    .def("getRewDim", &VecEnv::getRewDim)
	    .def("getRGBImage", &VecEnv::getRGBImage)
	    .def("getStereoImage", &VecEnv::getStereoImage)
	    .def("getDepthImage", &VecEnv::getDepthImage)
	    .def("getImgHeight", &VecEnv::getImgHeight)
	    .def("getImgWidth", &VecEnv::getImgWidth)
	    .def("getRewardNames", &VecEnv::getRewardNames)
	    .def("getCostAndGradient", &VecEnv::getCostAndGradient)
	    .def("__repr__", [](const VecEnv& a) { return "Flightmare Environment"; });
}