#ifndef PODBOAT_CONTROLLER_H_
#define PODBOAT_CONTROLLER_H_

#include <memory>
#include <string>
#include <vector>

#include "colormanager.h"
#include "configcontainer.h"
#include "download.h"
#include "fslock.h"
#include "keymap.h"
#include "queueloader.h"

namespace podboat {

class PbView;

class PbController {
public:
	PbController();
	~PbController() = default;

	void initialize(int argc, char* argv[]);
	int run(PbView& v);

	bool view_update_necessary() const
	{
		return view_update_;
	}
	void set_view_update_necessary(bool b)
	{
		view_update_ = b;
	}
	std::vector<Download>& downloads()
	{
		return downloads_;
	}

	std::string get_formatstr();

	unsigned int downloads_in_progress();
	void purge_queue();

	unsigned int get_maxdownloads();
	void start_downloads();

	void increase_parallel_downloads();
	void decrease_parallel_downloads();

	double get_total_kbps();

	void play_file(const std::string& str);

	newsboat::ConfigContainer* get_cfgcont()
	{
		return &cfg;
	}

	const newsboat::ColorManager& get_colormanager()
	{
		return colorman;
	}

private:
	void print_usage(const char* argv0);
	bool setup_dirs_xdg(const char* env_home);

	std::string config_file;
	std::string queue_file;
	newsboat::ConfigContainer cfg;
	bool view_update_;
	std::vector<Download> downloads_;

	std::string config_dir;
	std::string url_file;
	std::string cache_file;
	std::string searchfile;
	std::string cmdlinefile;

	unsigned int max_dls;

	std::unique_ptr<QueueLoader> ql;

	std::string lock_file;
	std::unique_ptr<newsboat::FsLock> fslock;

	bool automatic_dl = false;
	newsboat::ColorManager colorman;
	newsboat::KeyMap keys;
};

} // namespace podboat

#endif /* PODBOAT_CONTROLLER_H_ */
