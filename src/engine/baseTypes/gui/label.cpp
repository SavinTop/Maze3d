#include "label.hpp"

void Label::setText(std::string text) 
{
    this->text = text;
    textCharacters = guiText_getCharacters(text);
    maxHeight = calculateHeight();
    textWidth = calculateWidth()>>6;
}

void Label::setTextAlign(textAlign ta) 
{
    this->ta = ta;
}

void Label::__draw(oglw::Shader &program) 
{
    float scaleH = (float)this->h/maxHeight;
    float scaleW = (float)this->w/textWidth;
    float scale = glm::min(scaleH,scaleW);
    float tx = x-(float)w/2, ty = y-maxHeight*scale/2;

    if(ta == textAlign::Right){
        tx = tx+w-textWidth*scale;
    } else if(ta == textAlign::Center)
    {
        tx = tx+(w-textWidth*scale)/2.0f;
    }

    guiText_renderText(program, text, tx,ty,scale,glm::vec3(1.0));
}

int Label::calculateWidth() 
{
    int tempWidth = 0;
    for(auto& el:textCharacters)
        tempWidth+=el.Advance;
    return tempWidth;
}

int Label::calculateHeight() 
{   
    if(!textCharacters.size()) return 0;
    int tempHeight = textCharacters[0].Size.y;
    for(auto& el:textCharacters)
        if(el.Size.y>tempHeight) tempHeight = el.Size.y;
    return tempHeight;
}

Label::Label() : GuiObject(nullptr)
{
    ta = textAlign::Center;
    shaderType = guiShaderType::textShader;
}
