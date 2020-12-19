#include "maze.hpp"

ResourcePack mazeScene::getResources()
{
    ResourcePack temp;
    temp.setResources(menu->getResources().getRes());
    temp.getRes().insert(temp.getRes().begin(),{cornerWallModel.get(), rootWallModel.get(),
                          lineWallModel.get(), program.get(), cmt.get(), skyboxProgram.get(), cmo.get(),
                          floorTexture.get(), floorTextureNormal.get(), shadowProgram.get(),depthMapProgram.get()});
    return temp;
}

void mazeScene::initResources()
{
    menu = rm->createResource<>(MazeGui(window_w, window_h, rm), sceneName);
    cornerWallModel = rm->createResource(res::ogl::Model("data\\models\\cornerWall.obj"), sceneName, "cornerWallModel");
    rootWallModel = rm->createResource(res::ogl::Model("data\\models\\oneUnitWall.obj"), sceneName, "rootWallModel");
    lineWallModel = rm->createResource(res::ogl::Model("data\\models\\threeUnitWall.obj"), sceneName, "lineWallModel");
    program = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\basic\\shader.vert", "data\\shaders\\basic\\shader.frag", "basicShader"), sceneName);
    cmt = rm->createResource(res::ogl::CubemapTexture({
                                 "data\\skybox\\right.jpg",
                                 "data\\skybox\\left.jpg",
                                 "data\\skybox\\top.jpg",
                                 "data\\skybox\\bottom.jpg",
                                 "data\\skybox\\front.jpg",
                                 "data\\skybox\\back.jpg",
                             }),
                             sceneName, "skyboxTexture");
    skyboxProgram = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\skybox\\skybox.vert", "data\\shaders\\skybox\\skybox.frag", "skyboxShader"), sceneName);
    shadowProgram = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\shadow\\shadow.vert", "data\\shaders\\shadow\\skybox.frag", "shadowShader"), sceneName);
    depthMapProgram = rm->createResource(res::ogl::ShaderProgram("data\\shaders\\depthMap\\depth.vert", "data\\shaders\\depthMap\\depth.frag", "depthShader"), sceneName);
    cmo = rm->createResource(res::ogl::CubemapModel(cmt), sceneName, "Skybox model");
    floorTexture = rm->createResource(res::ogl::Texture("data\\models\\floorTextures\\floor_color.jpg"), sceneName);
    floorTextureNormal = rm->createResource(res::ogl::Texture("data\\models\\floorTextures\\Snow_003_NORM.jpg", res::ogl::TextureType::Normal), sceneName);
}