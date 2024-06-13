#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

// ������TLS Client
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

// ����TLS Client
// #include <websocketpp/config/asio_client.hpp>
// #include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>


#include <string>
#include <locale>
#include <codecvt>

typedef websocketpp::client<websocketpp::config::asio_client> client;

static std::wstring string_to_wstring(const std::string& s)
{
	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
	return conv.from_bytes(s);
}
static std::string wstring_to_string(const std::wstring& s)
{
	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
	return conv.to_bytes(s);
}
static std::string ansi_to_utf8(const std::string& s)
{
	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	return conv.to_bytes(string_to_wstring(s));
}
static std::string utf8_to_ansi(const std::string& s)
{
	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	return wstring_to_string(conv.from_bytes(s));
}


// ����һ�����ӵ�metadata
class connection_metadata {
public:
	typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

	connection_metadata(websocketpp::connection_hdl hdl, std::string url)
		: m_Hdl(hdl)
		, m_Status("Connecting")
		, m_Url(url)
		, m_Server("N/A")
	{}

	void on_open(client* c, websocketpp::connection_hdl hdl)
	{
		m_Status = "Open";

		client::connection_ptr con = c->get_con_from_hdl(hdl);
		m_Server = con->get_response_header("Server");
	}

	void on_fail(client* c, websocketpp::connection_hdl hdl)
	{
		m_Status = "Failed";

		client::connection_ptr con = c->get_con_from_hdl(hdl);
		m_Server = con->get_response_header("Server");
		m_Error_reason = con->get_ec().message();
	}

	void on_close(client* c, websocketpp::connection_hdl hdl)
	{
		m_Status = "Closed";
		client::connection_ptr con = c->get_con_from_hdl(hdl);
		std::stringstream s;
		s << "close code: " << con->get_remote_close_code() << " ("
			<< websocketpp::close::status::get_string(con->get_remote_close_code())
			<< "), close reason: " << con->get_remote_close_reason();
		m_Error_reason = s.str();
	}

	void on_message(websocketpp::connection_hdl, client::message_ptr msg)
	{
		if (msg->get_opcode() == websocketpp::frame::opcode::binary)
		{
			//std::string message = utf8_to_ansi(msg->get_payload());
			std::string message = (msg->get_payload());
			std::cout << "�յ����Է���������Ϣsize��" << message.length() << std::endl;
		}
		else
		{
			std::string message = websocketpp::utility::to_hex(msg->get_payload());
		}
	}

	websocketpp::connection_hdl get_hdl() const
	{
		return m_Hdl;
	}

	std::string get_status() const
	{
		return m_Status;
	}
private:
	websocketpp::connection_hdl m_Hdl;  // websocketpp��ʾ���ӵı��
	std::string m_Status;               // �����Զ�״̬
	std::string m_Url;                  // ���ӵ�URI
	std::string m_Server;               // ��������Ϣ
	std::string m_Error_reason;         // ����ԭ��
};


class WebsocketClient
{
public:
	WebsocketClient();
	virtual~WebsocketClient();

public:
	bool Connect(std::string const& url);
	bool Close(std::string reason = "");
	bool Send(std::string message);

	connection_metadata::ptr GetConnectionMetadataPtr();

private:
	connection_metadata::ptr m_ConnectionMetadataPtr;
	client m_WebsocketClient;
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_Thread; // �߳�
};


#endif // !WEBSOCKET_ENDPOINT_H
