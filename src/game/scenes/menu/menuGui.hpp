#pragma once

#include "baseTypes/gui/gui.hpp"
#include "baseTypes/resource/resource.hpp"
#include "game/maze_things/utils/dataHandler.hpp"
#include <GLFW/glfw3.h>

class MenuGui : public Resource{
public:
    MenuGui();
    MenuGui(int w, int h, ResourceManager* rm, GLFWwindow* wnd);

    void start();
    void draw();
    void load() override;
	void unload() override;
    void mouseInput(int x, int y, bool lb);

	virtual void InitializeSubResources(std::string groupName);
    std::vector<GuiObject*> getElements();
    std::vector<GuiObject*> getChildrenRecurs(GuiObject* curr);
    void initMain();
    void initEndless();
    void initTimed();
    void setExitButtonClickCallBack(std::function<void(void)> click);
    void setEndlessStartButtonClickCallBack(std::function<void(void)> click);
    void setTimedStartButtonClickCallBack(std::function<void(void)> click);
    int get_endless_lvl(){return endless_startLevel_value;}
    int get_timed_lvl(){return timed_startLevel_value;}

    void endlessClick();
    void timedClick();
    void helpClick();
    void back_click();
    void maze3d_click();


    void endless_leftArrowClick();
    void endless_rightArrowClick();
    void timed_leftArrowClick();
    void timed_rightArrowClick();
    void timed_update_res();

private:
    GLFWwindow* wnd;

    GuiWindow* currentWindow;
    GuiWindow main;
    GuiWindow endless;
    GuiWindow timed;
    int w,h;
    ResourceManager* rm;
    std::string spriteDirectory = "data\\scenes\\mainMenu\\sprites\\";

    FullscreenBox main_fbox;
    Button main_exit_button;
    Button main_timed_button;
    Button main_endless_button;
    Button main_help_button;
    Button main_maze3d_button;
    Button main_game_logo;

    FullscreenBox endless_fbox;
    Button endless_back_button;
    Button endless_leftArrow;
    Button endless_rightArrow;
    Button endless_start_button;
    Label endless_startLevel;
    int endless_startLevel_value;
    
    FullscreenBox timed_fbox;
    Button timed_back_button;
    Button timed_leftArrow;
    Button timed_rightArrow;
    Button timed_start_button;
    Label timed_startLevel;

    Label timed_min_text;
    Label timed_avg_text;
    Label timed_max_text;

    Label timed_min_value;
    Label timed_avg_value;
    Label timed_max_value;
    dataHandler timed_dh;

    int timed_startLevel_value;

    std::shared_ptr<res::ogl::Texture> exit_idle;
    std::shared_ptr<res::ogl::Texture> exit_active;
    std::shared_ptr<res::ogl::Texture> timed_idle;
    std::shared_ptr<res::ogl::Texture> timed_active;
    std::shared_ptr<res::ogl::Texture> endless_idle;
    std::shared_ptr<res::ogl::Texture> endless_active;
    std::shared_ptr<res::ogl::Texture> help_idle;
    std::shared_ptr<res::ogl::Texture> help_active;
    std::shared_ptr<res::ogl::Texture> back_idle;
    std::shared_ptr<res::ogl::Texture> back_active;
    std::shared_ptr<res::ogl::Texture> start_idle;
    std::shared_ptr<res::ogl::Texture> start_active;
    std::shared_ptr<res::ogl::Texture> maze3d_idle;
    std::shared_ptr<res::ogl::Texture> maze3d_active;

    std::shared_ptr<res::ogl::Texture> game_logo;

    //arrows

    std::shared_ptr<res::ogl::Texture> leftArrow_idle;
    std::shared_ptr<res::ogl::Texture> leftArrow_active;
    std::shared_ptr<res::ogl::Texture> rightArrow_idle;
    std::shared_ptr<res::ogl::Texture> rightArrow_active;

    std::shared_ptr<res::ogl::ShaderProgram> guiShader;

    bool lastMouseLeftButton;
};