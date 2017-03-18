#include "def.h"
#include <unistd.h>

main()
{
		int mytid;
		int tids[SLAVENUM];		/* slave task ids */
		char slave_name[NAMESIZE];
		int  inst,i, who;
		mytid=pvm_mytid();
		inst = pvm_joingroup(GROUPNAME);

		
				
		pvm_recv( -1, MSG_MSTR );
		pvm_upkint(&who, 1, 1 );
		pvm_upkint(&who,1,1 );
		printf("%d: %s\n",who, slave_name);
		
		char hostname[NAMESIZE];
		gethostname(hostname,sizeof hostname);
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&mytid,1,1);
		pvm_pkstr(hostname);
		pvm_send(who,MSG_MSTR);
		printf("group size: %d", pvm_gsize(GROUPNAME));
		pvm_lvgroup(GROUPNAME);

										pvm_exit();
}
