
#include "precomp.h"
#include "program.h"
#include "elapsed_timer.h"
#include "cache_provider.h"
#include <ClanLib/application.h>

using namespace clan;

Application clanapp(&Program::main);

int Program::main(const std::vector<std::string> &args)
{
	SetupCore setup_core;
	SetupDisplay setup_display;
	SetupD3D setup_d3d;

	DisplayWindow window("Scene3D Example", 1600, 900);

	GraphicContext gc = window.get_gc();

	bool exit = false;
	Slot slot_close = window.sig_window_close().connect_functor([&exit]() { exit = true; });

	SceneCache cache(new ExampleSceneCacheProvider());
	std::string shader_path = "../../../Resources/Scene3D";

	Scene scene(gc, cache, shader_path);

	SceneCamera camera(scene);

	scene.set_viewport(window.get_viewport());
	scene.set_camera(camera);

	ElapsedTimer elapsed_timer;

	while (!exit)
	{
		scene.update(gc, elapsed_timer.seconds_elapsed());

		gc.clear(Colorf::darkkhaki);
		scene.render(gc);
		
		window.flip(1);

		KeepAlive::process();
	}

	return 0;
}
