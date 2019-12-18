////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#undef SFML_OPENGL_ES
#define SFML_OPENGL_ES2

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "imgui.h"
#include "imgui_impl_opengl3.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    sf::Window window(sf::VideoMode(0, 0), "SFML graphics with OpenGL", sf::Style::Default, contextSettings); 

    // Make it the active window for OpenGL calls
    window.setActive();	
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontFromFileTTF("namyangju_godic.otf", 16.0f, NULL, io.Fonts->GetGlyphRangesKorean());
	io.MouseDrawCursor = true;
	io.DisplaySize = ImVec2((float)window.getSize().x, (float)window.getSize().y);	
	ImGui_ImplOpenGL3_Init(0); 	
	ImGui_ImplOpenGL3_NewFrame();
    // Our state
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// Main loop
    bool done = false;
	int mx, my;
    while (window.isOpen())
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		// Handle mouse events
		io.MousePos = ImVec2((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
		io.MouseDown[0] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		io.MouseDown[1] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		io.MouseDown[2] = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
		
        // Handle other events
        sf::Event event;
        while (window.pollEvent(event))
        {
			
		}			
        // Start the Dear ImGui frame
		ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
	
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
			static int counter = 0;

            ImGui::Begin("Hello, World!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
			ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("counter = %d, %d, %d", counter, (int)io.MousePos.x, (int)io.MousePos.y);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        //Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.display();
    }
	return 0;
}
