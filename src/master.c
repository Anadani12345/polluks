#include "def.h"

main()
{
	int mytid;
	int tids[SLAVENUM];		/* slave task ids */
	char slave_name[NAMESIZE];
	int nproc, i, who, inst;
	int bar;
	int MSG_TAG = 5;
	mytid = pvm_mytid();

	nproc=pvm_spawn(SLAVENAME, NULL, PvmTaskDefault, "", SLAVENUM, tids);
	inst = pvm_joingroup(GROUPNAME);
	pvm_bcast(GROUPNAME,MSG_TAG);
	bar = pvm_barrier(GROUPNAME,nproc);
	if(bar < 0) printf("Error");
	for( i=0 ; i<nproc ; i++ )
	{
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&mytid, 1, 1);
		pvm_pkint(&i, 1, 1);
		pvm_send(tids[i], MSG_MSTR);
	}

	for( i=0 ; i<nproc ; i++ )
	{
		pvm_recv( -1, MSG_SLV );
		pvm_upkint(&who, 1, 1 );
		pvm_upkstr(slave_name );
		printf("%d: %s\n",who, slave_name);
	}

	pvm_exit();
}

