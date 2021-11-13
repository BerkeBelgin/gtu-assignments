using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrowShrink : MonoBehaviour
{
    public GameObject gem1;
    public GameObject gem2;
    public float grow = 2F;
    private Vector3 gem1Scale;
    private Vector3 gem2Scale;
    // Start is called before the first frame update
    void Start()
    {
        gem1Scale = gem1.transform.localScale;
        gem2Scale = gem2.transform.localScale;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.GetTouch(0).position);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit))
            {
                if (hit.collider.gameObject.GetInstanceID() == gem1.GetInstanceID()) {
                    gem1.transform.localScale = new Vector3(gem1Scale.x * grow, gem1Scale.y * grow, gem1Scale.z * grow);
                    gem2.transform.localScale = gem2Scale;
                } else if (hit.collider.gameObject.GetInstanceID() == gem2.GetInstanceID()) {
                    gem1.transform.localScale = gem1Scale;
                    gem2.transform.localScale = new Vector3(gem2Scale.x * grow, gem2Scale.y * grow, gem2Scale.z * grow);
                } else {
                    gem1.transform.localScale = gem1Scale;
                    gem2.transform.localScale = gem2Scale;
                }
            }
        }
    }
}
