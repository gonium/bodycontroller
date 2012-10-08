#include <QApplication>
#include <libbodycontroller/common.hpp>
#include <libbodycontroller/gui_main_window.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/positional_options.hpp>
namespace po = boost::program_options;
namespace bfs=boost::filesystem;

int main (int argc, char* argv[]) {

  try {
    std::ostringstream oss;
    oss << "Usage: " << argv[0] << " ACTION [additional options]";
    po::options_description desc(oss.str());
    desc.add_options()
      ("help,h", "produce help message")
      ("version,v", "print version and exit")
      ("sequence,s", po::value<std::string>(), "the sequence file to use")
      ;
    po::positional_options_description p;
    p.add("sequence", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
        options(desc).positional(p).run(), vm);
    po::notify(vm);

    // Begin processing of commandline parameters.
    std::string sequencefile;

    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }

    if (vm.count("version")) {
      bodycontroller::VersionInfo::Ptr version(new bodycontroller::VersionInfo());
      std::cout << "bodycontroller version " << version->getVersion() << std::endl;
      return 0;
    }

//    if (! vm.count("sequence")) {
//      std::cerr << "You must specify a sequence file." << std::endl;
//      return 1;
//    } else {
//      sequencefile=vm["sequence"].as<std::string>();
//    }
//
//    bfs::path sequence(sequencefile);

    QApplication app(argc, argv);
//  Q_INIT_RESOURCE(sprites);

    try {
     //app.setStyle("plastique");
      bodycontroller::GUIMainWindow mainWindow;
      mainWindow.show();
      return app.exec();
    } catch (bodycontroller::GenericException& ex) {
      std::cout << "Caught exception: " << ex.what() << std::endl;
      exit(1);
    }
  } catch(std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  } catch(...) {
    std::cerr << "Exception of unknown type!" << std::endl;
    return 1;
  }
  return 0;
}


