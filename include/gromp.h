#ifndef __GROMP_H
#define __GROMP_H

typedef struct {

} gromp_server;

gromp_server *create_gromp_server();

void start_gromp_server(gromp_server *gromp);

void stop_gromp_server(gromp_server *gromp);

void destroy_gromp_server(gromp_server *gromp);

#endif // __GROMP_H