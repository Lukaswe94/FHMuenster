#ifndef UDP_EXAMPLES_SOCKET_H
#define UDP_EXAMPLES_SOCKET_H

#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Endpunkt für Kommunikation erstellen (Client und Server)
 * @param family Protokollfamilie: AF_INET (IPv4) oder AF_INET6 (IPv6)
 * @param type Übertragungsart der Daten: SOCK_STREAM (TCP) oder SOCK_DGRAM (UDP)
 * @param protocol Protokoll: 0 (Standardprotokoll, abhängig von type), IPPROTO_UDP oder IPPROTO_ICP
 * @return Dateideskriptor oder -1 (Fehler)
 */
int Socket(int family, int type, int protocol);

/**
 * @brief Verbindung zum Server-Socket herstellen (Client)
 * @param fd Dateideskriptor für den Client Socket
 * @param addr Struktur, in der die Protokollfamilie, Portnummer und IP-Adresse des Servers gespeichert ist, mit dem
 *        verbunden werden soll.
 *        Alternativ: sockaddr_in (zu sockaddr casten)
 * @param len Länge der Bytes von addr (mit sizeof)
 * @return 0 oder -1 (Fehler)
 */
int Connect(int fd, const struct sockaddr *addr, socklen_t len);

/**
 * @brief Socket-Deskriptor nach Datennübertragung freigeben (Client und Server)
 * @param fd Socket-Deskriptor
 * @return 0 oder -1 (Fehler)
 */
int Close(int fd);

/**
 * @brief IP-Adresse und Port des Servers festlegen, bzw. Socket mit Port an dem Datenpakete eingehen, verknüpfen (Server)
 * @param fd Socket-Deskriptor
 * @param addr Struktur, in der die Protokollfamilie, Portnummer und IP-Adresse des Servers gespeichert ist, mit dem der
 *        Socket verbunden werden soll.
 *        Alternativ: sockaddr_in (zu sockaddr casten).
 *        IP-Adresse auf INADDR_ANY setzen, damit Server über alle Netze erreichbar ist, ansonsten mit inet_addr()
 *        angeben.
 *        Falls Portnummer beliebig sein soll: 0 angeben (mit getsockname() abfragbar)
 * @param addrlen Länge der Bytes von addr (mit sizeof)
 * @return 0 oder -1 (Fehler)
 */
int Bind(int fd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * @brief Auf eingehende Verbindungen von Clients am Socket warten (Server)
 * @param fd Socket-Deskriptor
 * @param backlog Anzahl der maximal zu puffernden Verbindungsanforderungen
 * @return 0 oder -1 (Fehler)
 */
int Listen(int fd, int backlog);

/**
 * @brief Holt die nächste Verbindung aus Warteschlange (blockierend), die wir mit listen() eingerichtet haben (Server)
 * @param fd Socket-Deskriptor
 * @param addr Zeiger auf Adressstruktur, wo die Adresse des verbundenen Sockets gespeichert wird
 * @param len Zeiger auf eine Struktur, in der die Länge der Adresse gespeichert ist
 * @return Neuer Socket-Deskriptor mit selben Eigenschaften oder -1 (Fehler)
 */
int Accept(int fd, struct sockaddr *addr, socklen_t *len);

/**
 * @brief Datenpakete vom Socket empfangen (Client und Server)
 * @param fd Socket-Deskriptor von dem gelesen werden soll
 * @param buf Zeiger auf Speicherbereich, indem das Datenpaket abgelegt werden soll
 * @param buflen Länge des Speicherbereichs
 * @param flags Standardmäßig 0 angeben
 * @param from Zeiger auf Ursprungstransportadresse, selbe wie in Connect()
 * @param addrlen Länge der Bytes von from (mit sizeof)
 * @return Anzahl der gelesenen Bytes oder -1 (Fehler)
 */
ssize_t Recvfrom(int fd, void *buf, size_t buflen, int flags, struct sockaddr *from, socklen_t *addrlen);

/**
 * @brief Datenpakete an Socket schicken (Client und Server)
 * @param fd Socket-Deskriptor an den gesendet werden soll
 * @param buf Zeiger auf Speicherbereich, dessen Daten gesendet werden soll
 * @param buflen Länge des Speicherbereichs
 * @param flags Standardmäßig auf 0
 * @param to Zeiger auf auf Zieltransportadresse, selbe wie in Connect()
 * @param addrlen Länge der Bytes von to (mit sizeof)
 * @return Anzahl der gesendeten Bytes oder -1 (Fehler)
 */
ssize_t Sendto(int fd, void *buf, size_t buflen, int flags, const struct sockaddr *to, socklen_t addrlen);

/**
 * @brief Alternative zu Recvfrom, wobei fom und addrlen weggelassen wird, da Socket im Connected-Zustand ist (Client und Server)
 * @param fd Socket-Deskriptor
 * @param buf Zeiger auf Speicherbereich, dessen Daten gesendet werden soll
 * @param buflen Länge des Speicherbereichs
 * @param flags Standardmäßig auf 0
 * @return Anzahl der gesendeten Bytes oder -1 (Fehler)
 */
ssize_t Recv(int fd, void *buf, size_t buflen, int flags);

/**
 * @brief Alternative zu Sendto, wobei to und addrlen weggelassen wird, da Socket im Connected-Zustand ist (Client und Server)
 * @param fd Socket-Deskriptor
 * @param buf Zeiger auf Speicherbereich, dessen Daten gesendet werden soll
 * @param buflen Länge des Speicherbereichs
 * @param flags tandardmäßig auf 0
 * @return Anzahl der gesendeten Bytes oder -1 (Fehler)
 */
ssize_t Send(int fd, void *buf, size_t buflen, int flags);

/**
 * @brief Schaltet das Senden und/oder Empfangen von Daten an einem Socket aus (Client und Server)
 * @param fd Socket-Deskriptor
 * @param how Weiteren Empfang ausschalten (SHUT_RD).
 *            Weitere Sendung ausschalten (SHUT_WR).
 *            Weiteren Empfang und weitere Sendung ausschalten (SHUT_RDWR)
 * @return 0 oder -1 (Fehler)
 */
int Shutdown(int fd, int how);

#endif //UDP_EXAMPLES_SOCKET_H
