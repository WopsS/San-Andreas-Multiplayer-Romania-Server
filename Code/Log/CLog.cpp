#include <Log/CLog.hpp>
#include <Utilities/Time.hpp>

CLog::CLog()
	: m_shouldStop(false)
{
	m_file.open("server_log.html", std::ios::out);

	m_file << "<!DOCTYPE HTML><html><head><title>MySQL Plugin log</title><meta charset=\"utf-8\"/><style type=text/css>body{color:#232323;background-color:#eee;font-family:'Trebuchet MS',sans-serif;font-size:90%}.panel{margin-bottom:20px;background-color:#fff;border:1px solid transparent;border-radius:4px;-webkit-box-shadow:0 1px 1px rgba(0,0,0,.05);box-shadow:0 1px 1px rgba(0,0,0,.05);width:75%;position:relative;top:50px;margin-left:50px;margin-right:auto}.panel-heading{border-bottom:1px solid #ddd;border-top-left-radius:3px;border-top-right-radius:3px;padding:10px 15px;color:#333;font-size:150%;background-color:#f5f5f5}.panel-heading-center{border-bottom:1px solid #ddd;padding:10px 15px;color:#333;font-size:150%;background-color:#f5f5f5;text-align:center}.panel-body{padding:15px}.panel-default{border-color:#ddd}.panel-footer{padding:10px 15px;background-color:#f5f5f5;border-bottom-right-radius:3px;border-bottom-left-radius:3px}.panel-right{margin-bottom:20px;background-color:#fff;border:1px solid transparent;border-radius:4px;-webkit-box-shadow:0 1px 1px rgba(0,0,0,.05);box-shadow:0 1px 1px rgba(0,0,0,.05);width:200px;top:58px;position:fixed;right:0}.panel-right-default{border-color:#ddd}.label{display:inline-block;padding:.2em .6em .3em;line-height:1;color:#fff;text-align:center;white-space:nowrap;vertical-align:baseline;border-radius:.25em}.label-error{background-color:#bf0000;margin-bottom:5px}.label-warning{background-color:orange;margin-bottom:5px}.label-debug{background-color:#090;margin-bottom:5px}table{max-width:100%;background-color:transparent;border-collapse:collapse!important;width:100%;text-align:center;table-layout:fixed;overflow-x:auto;white-space:pre-wrap;white-space:-moz-pre-wrap!important;white-space:pre-wrap;white-space:-o-pre-wrap;word-wrap:break-word}tr.second,th.second,td.second{padding:8px;vertical-align:central;border-bottom:1px solid #ddd;border-left:1px solid #ddd;text-align:center}td.first,th.first{border-left:none;border-bottom:1px solid #ddd}tbody{text-align:center}.Time{width:10%}.Status{width:8%}@media screen and (max-width:812px){table{overflow-x:auto;display:block}.panel-right{display:none}}@media screen and (max-width:1000px) and (min-width:813px){.panel-right{width:150px;overflow-x:auto;display:block}.label-error{background-color:#bf0000;margin-bottom:5px;overflow-x:auto;white-space:pre-wrap;white-space:-moz-pre-wrap!important;white-space:pre-wrap;white-space:-o-pre-wrap;word-wrap:break-word}.label-warning{background-color:orange;margin-bottom:5px;overflow-x:auto;white-space:pre-wrap;white-space:-moz-pre-wrap!important;white-space:pre-wrap;white-space:-o-pre-wrap;word-wrap:break-word}.label-debug{background-color:#090;margin-bottom:5px;overflow-x:auto;white-space:pre-wrap;white-space:-moz-pre-wrap!important;white-space:pre-wrap;white-space:-o-pre-wrap;word-wrap:break-word}}</style><script type=text/javascript>var LOG_DEBUG=1,LOG_WARNING=2,LOG_ERROR=3,debugMessages=0,warningMessages=0,errorMessages=0,isPanelOpen=false,isTableOpen=false;function OpenPanel(a,b){if(isPanelOpen==true){ClosePanel()}document.write(\"<div class='panel panel-default'><div class='panel-heading\"+(b==true?\"-center\":\"\")+\"'>\"+(a!=null?a:\"\")+\"</div>\");isPanelOpen=true}function ClosePanel(a){if(isPanelOpen==true){document.write(\"</table><div class='panel-footer'>\"+(a!=null?a:\"\")+\"</div></div>\");document.write(\"<div class='panel-right panel-right-default '><div class='panel-heading'>Log info</div><div class='panel-body'><span class='label label-debug'>Debug messages: \"+debugMessages+\"</span> <span class='label label-warning'>Warning messages: \"+warningMessages+\"</span> <span class='label label-error'>Error messages: \"+errorMessages+\"</span></div>\");document.write(\"<div class='panel-footer' align='center'>MySQL <strong>" << MYSQL_VERSION << "</strong><div></div>\");isPanelOpen=false;CloseTable()}}function OpenTable(){if(isTableOpen==true){CloseTable()}document.write(\"<table class='table'>\");document.write(\"<thead><tr><th class='Time first'>Time</th><th class='Status second'>Status</th><th class='second'>Message</th></tr></thead>\");document.write(\"<tbody>\");isTableOpen=true}function CloseTable(){if(isTableOpen==true){document.write(\"</tbody></table>\");isTableOpen=false}}function Log(b,a,e){if(isPanelOpen==false){OpenPanel()}if(isTableOpen==false){OpenTable()}var d,c;switch(a){case LOG_DEBUG:d=\"#009900\";c=\"OK\";debugMessages++;break;case LOG_WARNING:d=\"orange\";c=\"WARNING\";warningMessages++;break;case LOG_ERROR:d=\"#bf0000\";c=\"ERROR\";errorMessages++;break}document.write(\"<tr bgcolor = \"+d+\"><td class='Time first'> \"+b+\"</td><td class='Status second'>\"+c+\"</td><td class='second'>\"+e+\"</td></tr>\")};</script></head><body><script>OpenPanel(\"Logging started at " << Time::GetTime() << "\");ClosePanel(\"Logging ended at " << Time::GetTime() << "\");</script></body></html>";
	m_file.flush();

	m_thread = std::make_unique<std::thread>(std::bind(&CLog::Process, this));
}

CLog::~CLog()
{
	bool IsEmpty = false;

	while (IsEmpty == false)
	{
		m_queueMutex.lock();
		IsEmpty = m_queue.empty();
		m_queueMutex.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}

	m_shouldStop.store(true);
	m_thread->join();

	m_file.close();
}

void CLog::Process()
{
	while (m_shouldStop.load(std::memory_order::memory_order_acquire) == false)
	{
		m_queueMutex.lock();

		try
		{
			// Check if queue has elements.
			if (m_queue.empty() == false)
			{
				std::streampos currentPosition = m_file.tellp(), deletePosition = 63;
				m_file.seekp(currentPosition - deletePosition);

				while (m_queue.empty() == false)
				{
					auto Information = std::move(m_queue.front());
					m_queue.pop();

					m_file << fmt::format("Log(\"{}\", {}, \"{}\");", Time::GetTime(), Information->Level, Information->Message);
				}

				m_file << fmt::format("ClosePanel(\"Logging ended at {}\");</script></body></html>", Time::GetTime());
				m_file.flush();
			}
		}
		catch (std::exception e)
		{
			sampgdk::logprintf(fmt::format("CLog::Process - exception {}", e.what()).c_str());
		}

		m_queueMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
