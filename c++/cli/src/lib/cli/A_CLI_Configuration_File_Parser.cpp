/**
 * @file    A_CLI_Configuration_File_Parser.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Configuration_File_Parser.hpp"

// CLI Libraries
#include "../thirdparty/pugixml.hpp"
#include "cmd/A_CLI_Command_Parser_Factory.hpp"
#include "A_CLI_Connection_Handler_Local_Config.hpp"
#include "A_CLI_Connection_Handler_Socket_Config.hpp"

// C++ Standard Libraries
#include <iostream>
#include <sstream>

// Boost Libraries
#include <boost/filesystem.hpp>

namespace CLI{


/************************************/
/*          Constructor             */
/************************************/
A_CLI_Configuration_File_Parser::A_CLI_Configuration_File_Parser( const std::string& config_path )
  : m_class_name("A_CLI_Configuration_File_Parser"),
    m_config_pathname(config_path),
    m_current_configuration(A_CLI_Manager_Configuration(CLIConnectionType::LOCAL)),
    m_is_valid(false)
{
    // Parse the file
    Parse_Configuration_File();
}


/********************************************/
/*      Parse the Configuration File        */
/********************************************/
void A_CLI_Configuration_File_Parser::Parse_Configuration_File()
{

    /// List of queries
    const std::string CONNECTION_TYPE_QUERY   = "connection-type";
    const std::string COMMAND_CONFIG_NODE     = "command-configuration";
    const std::string CLI_CONFIG_QUERY        = "cli";
    const std::string CLI_TITLE_QUERY         = "title";
    const std::string CLI_COMMAND_QUEUE_QUERY = "command-queue"; 

    // Temp Variables
    std::string temp_str;
    int temp_int;

    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( m_config_pathname.c_str() );

    if( result == false ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Configuration File parsed with errors. Details: " << result.description();
        std::cerr << sin.str() << std::endl;
        return;
    }

    
    // Get the root node
    pugi::xml_node root_node = xmldoc.child("cli-manager-configuration");

    // Check the node
    if( root_node == pugi::xml_node() ){ return; }

    

    // Check the connection type
    CLIConnectionType cli_conn_type = StringToCLIConnectionType( root_node.child(CONNECTION_TYPE_QUERY.c_str()).attribute("value").as_string());
    if( cli_conn_type == CLIConnectionType::UNKNOWN ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Connection Type value is invalid.";
        std::cerr << sin.str() << std::endl;
        return;
    }
    m_current_configuration.Set_CLI_Connection_Type( cli_conn_type );

    
    // If we are Local, then load the local configuration
    if( cli_conn_type == CLIConnectionType::LOCAL ){

        m_connection_handler_config = std::make_shared<A_CLI_Connection_Handler_Local_Config>();
        m_current_configuration.Set_CLI_Connection_Handler_Config( m_connection_handler_config );
    }
    else if( cli_conn_type == CLIConnectionType::SOCKET ){

        // Socket Config
        pugi::xml_node socket_config_node = root_node.child("socket-configuration");

        // Get the port number
        int portno = socket_config_node.child("listening-port").attribute("value").as_int();

        // Create the configuration
        m_connection_handler_config = std::make_shared<A_CLI_Connection_Handler_Socket_Config>( portno );
        m_current_configuration.Set_CLI_Connection_Handler_Config( m_connection_handler_config );

        // set the window size
        m_current_configuration.Set_Socket_Window_Cols( socket_config_node.child("window-size").attribute("cols").as_int(100));
        m_current_configuration.Set_Socket_Window_Rows( socket_config_node.child("window-size").attribute("rows").as_int(20));
    }

    // Get the Command Parser config file
    temp_str = root_node.child(COMMAND_CONFIG_NODE.c_str()).attribute("path").as_string();
    
    // make sure it exists
    if( boost::filesystem::exists( temp_str ) == false ){
        std::cerr << "error:  " << temp_str << " does not exist." << std::endl;
        return;
    }

    // Set the parser
    m_current_configuration.Set_CLI_Command_Parser( CMD::A_CLI_Command_Parser_Factory::Initialize( temp_str ));

    // Grab the CLI Node
    pugi::xml_node cli_node = root_node.child(CLI_CONFIG_QUERY.c_str());

    // Get the CLI title
    temp_str = cli_node.child(CLI_TITLE_QUERY.c_str()).attribute("value").as_string();
    if( temp_str == "" ){
        temp_str = "Console";
    }
    m_current_configuration.Set_CLI_Title( temp_str );

    // Get the CLI Command Queue Max Size
    temp_int = cli_node.child( CLI_COMMAND_QUEUE_QUERY.c_str()).attribute("max_size").as_int();
    if( temp_int <= 0 ){
        std::cerr << "CLI Command Queue Max Size must be > 0" << std::endl;
        return;
    }
    m_current_configuration.Set_CLI_Command_Queue_Max_Size( temp_int );

    // Set valid
    m_is_valid = true;
}



} // End of CLI Namespace
